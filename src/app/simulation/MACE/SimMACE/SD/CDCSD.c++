#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Math/MidPoint.h++"
#include "MACE/SimMACE/Analysis.h++"
#include "MACE/SimMACE/Region.h++"
#include "MACE/SimMACE/SD/CDCSD.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4HCofThisEvent.hh"
#include "G4ProductionCuts.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include "gsl/gsl"

#include <algorithm>
#include <bit>
#include <cstdint>
#include <numeric>

namespace MACE::SimMACE::inline SD {

CDCSD::CDCSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fEventID{-1},
    fHitsCollection{},
    fMeanDriftVelocity{},
    fDeadTime{},
    fCellMap{},
    fCellEntryPoint{},
    fCellSignalTimesAndHit{} {
    collectionName.emplace_back(sdName + "HC");
}

void CDCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new CDCHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);

    const auto& cdc = Detector::Description::CDC::Instance();
    fMeanDriftVelocity = cdc.MeanDriftVelocity();
    fDeadTime = cdc.DeadTime();
    fCellMap = &cdc.CellMap();
}

G4bool CDCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) {
    const auto& step = *theStep;
    const auto& track = *step.GetTrack();
    const auto& particle = *track.GetDefinition();

    if (track.GetCurrentStepNumber() <= 1 or particle.GetPDGCharge() == 0) {
        return false;
    }

    const auto trackID = track.GetTrackID();
    const auto& touchable = *track.GetTouchable();
    const auto cellID = touchable.GetReplicaNumber();

    const auto SaveHit =
        [&](const G4StepPoint& entryPoint, const G4StepPoint& exitPoint) {
            const auto position{Math::MidPoint(entryPoint.GetPosition(), exitPoint.GetPosition())};
            const auto energy{Math::MidPoint(entryPoint.GetKineticEnergy(), exitPoint.GetKineticEnergy())};
            const auto momentum{Math::MidPoint(entryPoint.GetMomentum(), exitPoint.GetMomentum())};
            // retrive wire position
            const auto& cellInfo = fCellMap->at(cellID);
            const auto xWire{VectorCast<G4TwoVector>((*fCellMap)[cellID].position)};
            const auto tWire{VectorCast<G4ThreeVector>((*fCellMap)[cellID].direction)};
            // calculate drift distance
            const auto commonNormal{tWire.cross(momentum)};
            const auto driftDistance{std::abs((position - xWire).dot(commonNormal)) / commonNormal.mag()};
            const auto driftTime{driftDistance / fMeanDriftVelocity};
            const auto signalTime{Math::MidPoint(entryPoint.GetGlobalTime(), exitPoint.GetGlobalTime()) + driftTime};
            // retrive vertex energy and momentum
            const auto vertexEk{track.GetVertexKineticEnergy()};
            const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
            // new a hit
            auto hit = std::make_unique_for_overwrite<CDCHit>();
            Get<"CellID">(*hit) = cellID;
            Get<"t">(*hit) = signalTime;
            Get<"tD">(*hit) = driftTime;
            Get<"d">(*hit) = driftDistance;
            Get<"EvtID">(*hit) = fEventID;
            Get<"TrkID">(*hit) = trackID;
            Get<"PDGID">(*hit) = particle.GetPDGEncoding();
            Get<"Ek">(*hit) = energy;
            Get<"x">(*hit) = position;
            Get<"p">(*hit) = momentum;
            Get<"t0">(*hit) = track.GetGlobalTime() - track.GetLocalTime();
            Get<"x0">(*hit) = track.GetVertexPosition();
            Get<"Ek0">(*hit) = vertexEk;
            Get<"p0">(*hit) = vertexMomentum;
            fCellSignalTimesAndHit[cellID].emplace_back(signalTime, std::move(hit));
        };

    const auto& nextReigon = static_cast<Region&>(*track.GetNextVolume()->GetLogicalVolume()->GetRegion());

    if (step.IsFirstStepInVolume() and step.IsLastStepInVolume() and // is entering and exiting,
        nextReigon.Type() != RegionType::CDCSenseWire) {             // but the track is not heading into sense wire.
        SaveHit(*step.GetPreStepPoint(), *step.GetPostStepPoint());
        fCellEntryPoint.erase({cellID, trackID});
        return true;
    }

    if (step.IsFirstStepInVolume()) {
        fCellEntryPoint.try_emplace({cellID, trackID}, *step.GetPreStepPoint());
        return false;
    }
    if (decltype(fCellEntryPoint.cbegin()) monitoring;
        step.IsLastStepInVolume() and                                                       // is exiting,
        nextReigon.Type() != RegionType::CDCSenseWire and                                   // but the track is not heading into sense wire,
        (monitoring = fCellEntryPoint.find({cellID, trackID})) != fCellEntryPoint.cend()) { // and make sure it has entered before.
        // save the hit
        SaveHit(monitoring->second, *step.GetPostStepPoint());
        // particle is exiting, remove it from monitoring list
        fCellEntryPoint.erase(monitoring);
        return true;
    }

    return false;
}

void CDCSD::EndOfEvent(G4HCofThisEvent*) {
    fCellEntryPoint.clear();

    auto& hitList = *fHitsCollection->GetVector();
    hitList.reserve(
        std::accumulate(fCellSignalTimesAndHit.cbegin(), fCellSignalTimesAndHit.cend(), 0ull,
                        [](const auto& count, const auto& value) {
                            return count + value.second.size();
                        }));

    for (auto&& [_, signalTimesAndHit] : fCellSignalTimesAndHit) {
        if (signalTimesAndHit.size() == 1) {
            hitList.emplace_back(signalTimesAndHit.front().second.release());
        } else {
            std::ranges::sort(signalTimesAndHit);
            std::vector<std::unique_ptr<CDCHit>*> signalHitCandidateList;
            auto signalTimeThreshold = signalTimesAndHit.front().first + fDeadTime;
            for (auto timeHit = signalTimesAndHit.begin(); timeHit != signalTimesAndHit.end(); ++timeHit) {
                signalHitCandidateList.emplace_back(&timeHit->second);
                if (const auto signalTime = timeHit->first;
                    signalTime > signalTimeThreshold or timeHit == std::prev(signalTimesAndHit.end())) {
                    const auto goodHit =
                        *std::ranges::max_element(std::as_const(signalHitCandidateList),
                                                  [](auto&& hit1, auto&& hit2) {
                                                      return Get<"Ek">(**hit1) < Get<"Ek">(**hit2);
                                                  });
                    hitList.emplace_back(goodHit->release());
                    signalHitCandidateList.clear();
                    signalTimeThreshold = signalTime + fDeadTime;
                }
            }
        }
        signalTimesAndHit.clear();
    }

    Analysis::Instance().SubmitSpectrometerHC(&hitList);
}

} // namespace MACE::SimMACE::inline SD
