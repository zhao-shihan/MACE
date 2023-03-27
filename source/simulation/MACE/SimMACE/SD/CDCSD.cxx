#include "MACE/Detector/Description/CDC.hxx"
#include "MACE/Math/MidPoint.hxx"
#include "MACE/SimMACE/Analysis.hxx"
#include "MACE/SimMACE/Region.hxx"
#include "MACE/SimMACE/SD/CDCSD.hxx"
#include "MACE/Utility/VectorCast.hxx"

#include "G4HCofThisEvent.hh"
#include "G4ProductionCuts.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include "gsl/gsl"

#include <algorithm>
#include <numeric>

namespace MACE::SimMACE::inline SD {

CDCSD::CDCSD(const G4String& sdName) :
    NonMoveableBase(),
    G4VSensitiveDetector(sdName),
    fEventID(-1),
    fHitsCollection(nullptr),
    fMeanDriftVelocity(),
    fHalfTimeResolution(),
    fCellEntryPoints(),
    fCellMap(),
    fCellSignalTimesAndHits() {
    const auto& cellMap = Detector::Description::CDC::Instance().CellMap();
    fCellEntryPoints.resize(cellMap.size());
    fCellMap.reserve(cellMap.size());
    for (auto&& cell : cellMap) {
        fCellMap.emplace_back(VectorCast<G4TwoVector>(cell.position),
                              VectorCast<G4ThreeVector>(cell.direction));
    }
    fCellSignalTimesAndHits.resize(cellMap.size());

    collectionName.insert(sdName + "HC");
}

void CDCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new CDCHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);

    const auto& cdc = Detector::Description::CDC::Instance();
    fMeanDriftVelocity = cdc.MeanDriftVelocity();
    fHalfTimeResolution = cdc.TimeResolution() / 2;
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
            const auto time = Math::MidPoint(entryPoint.GetGlobalTime(), exitPoint.GetGlobalTime());
            const auto position = Math::MidPoint(entryPoint.GetPosition(), exitPoint.GetPosition());
            const auto energy = Math::MidPoint(entryPoint.GetTotalEnergy(), exitPoint.GetTotalEnergy());
            const auto momentum = Math::MidPoint(entryPoint.GetMomentum(), exitPoint.GetMomentum());
            // retrive wire position
            const auto& [xWire, tWire] = fCellMap[cellID];
            // calculate drift distance
            const auto commonNormal = tWire.cross(momentum);
            const auto driftDistance = std::abs((position - xWire).dot(commonNormal)) / commonNormal.mag();
            // calculate vertex energy and momentum
            const auto vertexTotalEnergy = track.GetVertexKineticEnergy() + particle.GetPDGMass();
            const auto vertexMomentum = track.GetVertexMomentumDirection() * std::sqrt(track.GetVertexKineticEnergy() * (vertexTotalEnergy + particle.GetPDGMass()));
            // new a hit
            auto hit = std::make_unique_for_overwrite<CDCHit>();
            hit->HitTime(time);
            hit->DriftDistance(driftDistance);
            hit->CellID(cellID);
            hit->G4EventID(fEventID);
            hit->G4TrackID(trackID);
            hit->PDGCode(particle.GetPDGEncoding());
            hit->Energy(energy);
            hit->Momentum(momentum);
            hit->VertexTime(track.GetGlobalTime() - track.GetLocalTime());
            hit->VertexPosition(track.GetVertexPosition());
            hit->VertexEnergy(vertexTotalEnergy);
            hit->VertexMomentum(vertexMomentum);
            fCellSignalTimesAndHits[cellID].emplace_back(hit->HitTime().Value() + driftDistance / fMeanDriftVelocity,
                                                         std::move(hit));
        };

    const auto& nextReigon = static_cast<Region&>(*track.GetNextVolume()->GetLogicalVolume()->GetRegion());
    auto& entryPointList = fCellEntryPoints[cellID];

    if (step.IsFirstStepInVolume() and step.IsLastStepInVolume() and // is entering and exiting,
        nextReigon.Type() != RegionType::CDCSenseWire) {             // but the track is not heading into sense wire.
        SaveHit(*step.GetPreStepPoint(), *step.GetPostStepPoint());
        entryPointList.erase(trackID);
        return true;
    }

    if (step.IsFirstStepInVolume()) {
        entryPointList.try_emplace(trackID, *step.GetPostStepPoint());
        return false;
    }
    if (decltype(entryPointList.cbegin()) monitoring;
        step.IsLastStepInVolume() and                                           // is exiting,
        nextReigon.Type() != RegionType::CDCSenseWire and                       // but the track is not heading into sense wire,
        (monitoring = entryPointList.find(trackID)) != entryPointList.cend()) { // and make sure it has entered before.
        // save the hit
        SaveHit(monitoring->second, *step.GetPreStepPoint());
        // particle is exiting, remove it from monitoring list
        entryPointList.erase(monitoring);
        return true;
    }

    return false;
}

void CDCSD::EndOfEvent(G4HCofThisEvent*) {
    for (auto&& entryPointList : fCellEntryPoints) {
        entryPointList.clear();
    }

    auto& hits = *fHitsCollection->GetVector();
    hits.reserve(
        std::accumulate(fCellSignalTimesAndHits.cbegin(), fCellSignalTimesAndHits.cend(), 0ull,
                        [](const auto& count, const auto& signalTimesAndHits) {
                            return count + signalTimesAndHits.size();
                        }));

    for (auto&& signalTimesAndHits : fCellSignalTimesAndHits) {
        if (signalTimesAndHits.empty()) { continue; }

        std::ranges::sort(signalTimesAndHits);

        std::vector<std::unique_ptr<CDCHit>*> signalHitCandidateList;
        auto signalTimeThreshold = signalTimesAndHits.front().first + fHalfTimeResolution;
        for (auto timeHit = signalTimesAndHits.begin(); timeHit != signalTimesAndHits.end(); ++timeHit) {
            signalHitCandidateList.emplace_back(&timeHit->second);
            const auto signalTime = timeHit->first;
            if (signalTime > signalTimeThreshold or timeHit == std::prev(signalTimesAndHits.end())) {
                const auto goodHit =
                    *std::ranges::max_element(signalHitCandidateList,
                                              [](const auto& hit1, const auto& hit2) {
                                                  return (*hit1)->Energy().Value() < (*hit2)->Energy().Value();
                                              });
                hits.emplace_back(goodHit->release());
                signalHitCandidateList.clear();
                signalTimeThreshold = signalTime + fHalfTimeResolution;
            }
        }

        signalTimesAndHits.clear();
    }

    Analysis::Instance().SubmitSpectrometerHC(&hits);
}

} // namespace MACE::SimMACE::inline SD
