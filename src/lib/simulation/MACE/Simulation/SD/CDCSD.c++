#include "MACE/Math/MidPoint.h++"
#include "MACE/Simulation/SD/CDCSD.h++"
#include "MACE/Utility/VectorArithmeticOperator.h++"
#include "MACE/Utility/VectorCast.h++"

#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <string_view>
#include <utility>

namespace MACE::inline Simulation::inline SD {

CDCSD::CDCSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fEventID{-1},
    fMeanDriftVelocity{},
    fCellMap{},
    fSplitHit{},
    fHitsCollection{} {
    collectionName.emplace_back(sdName + "HC");
}

auto CDCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    const auto& cdc{Detector::Description::CDC::Instance()};
    fMeanDriftVelocity = cdc.MeanDriftVelocity();
    fCellMap = &cdc.CellMap();

    fHitsCollection = new CDCHitCollection(SensitiveDetectorName, collectionName[0]);
    const auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto CDCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (particle.GetPDGCharge() == 0) { return false; }

    const auto eDep{step.GetTotalEnergyDeposit()};

    if (eDep - step.GetNonIonizingEnergyDeposit() == 0) { return false; } // ionizing Edep
    assert(eDep > 0);

    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto& postStepPoint{*step.GetPostStepPoint()};
    const auto cellID{preStepPoint.GetTouchable()->GetReplicaNumber()};
    const auto kineticEnergy{Math::MidPoint(preStepPoint.GetKineticEnergy(), postStepPoint.GetKineticEnergy())};
    const auto position{Math::MidPoint(preStepPoint.GetPosition(), postStepPoint.GetPosition())};
    const auto momentum{Math::MidPoint(preStepPoint.GetMomentum(), postStepPoint.GetMomentum())};
    // retrive wire position
    const auto& cellInfo{fCellMap->at(cellID)};
    const auto xWire{VectorCast<G4TwoVector>(cellInfo.position)};
    const auto tWire{VectorCast<G4ThreeVector>(cellInfo.direction)};
    // calculate drift distance
    const auto commonNormal{tWire.cross(momentum)};
    const auto driftDistance{std::abs((position - xWire).dot(commonNormal)) / commonNormal.mag()};
    const auto driftTime{driftDistance / fMeanDriftVelocity};
    const auto hitTime{Math::MidPoint(preStepPoint.GetGlobalTime(), postStepPoint.GetGlobalTime())};
    const auto signalTime{hitTime + driftTime};
    // vertex Ek and p
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // assert event ID
    assert(fEventID >= 0);
    // new a hit
    auto hit{std::make_unique_for_overwrite<CDCHit>()};
    Get<"EvtID">(*hit) = fEventID;
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"CellID">(*hit) = cellID;
    Get<"t">(*hit) = signalTime;
    Get<"tD">(*hit) = driftTime;
    Get<"d">(*hit) = driftDistance;
    Get<"Edep">(*hit) = eDep;
    Get<"tHit">(*hit) = hitTime;
    Get<"Ek">(*hit) = kineticEnergy;
    Get<"x">(*hit) = position;
    Get<"p">(*hit) = momentum;
    Get<"TrkID">(*hit) = track.GetTrackID();
    Get<"PDGID">(*hit) = particle.GetPDGEncoding();
    Get<"t0">(*hit) = track.GetGlobalTime() - track.GetLocalTime();
    Get<"x0">(*hit) = track.GetVertexPosition();
    Get<"Ek0">(*hit) = vertexEk;
    Get<"p0">(*hit) = vertexMomentum;
    *Get<"CreatProc">(*hit) = creatorProcess ? std::string_view{creatorProcess->GetProcessName()} : "|0>";
    fSplitHit[cellID].emplace_back(std::move(hit));

    return true;
}

auto CDCSD::EndOfEvent(G4HCofThisEvent*) -> void {
    const auto timeResolutionFWHM{Detector::Description::CDC::Instance().TimeResolutionFWHM()};

    for (int hitID{};
         auto&& [cellID, splitHit] : fSplitHit) {
        switch (splitHit.size()) {
        case 0:
            break;
        case 1: {
            auto& hit{splitHit.front()};
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"CellID">(*hit) == cellID);
            fHitsCollection->insert(hit.release());
            splitHit.clear();
        } break;
        default: {
            // sort hit by signal time
            std::ranges::sort(splitHit,
                              [](const auto& hit1, const auto& hit2) {
                                  return Get<"t">(*hit1) < Get<"t">(*hit2);
                              });
            // loop over all hits on this cell and cluster to real hits by signal times
            auto windowClosingTime{Get<"t">(*splitHit.front()) + timeResolutionFWHM};
            std::vector<std::unique_ptr<CDCHit>*> hitCandidate;
            for (auto&& aSplitHit : splitHit) {
                const auto timeWindowClosed{Get<"t">(*aSplitHit) > windowClosingTime};
                if (not timeWindowClosed) {
                    hitCandidate.emplace_back(&aSplitHit);
                }
                if (timeWindowClosed or aSplitHit == splitHit.back()) {
                    // find top hit
                    const auto iTopHit{std::ranges::min_element(std::as_const(hitCandidate),
                                                                [](const auto& hit1, const auto& hit2) {
                                                                    return Get<"TrkID">(**hit1) < Get<"TrkID">(**hit2);
                                                                })};
                    const auto topHit{*iTopHit};
                    // construct real hit
                    Get<"HitID">(**topHit) = hitID++;
                    assert(Get<"CellID">(**topHit) == cellID);
                    int nTopHit{};
                    for (auto&& hit : std::as_const(hitCandidate)) {
                        if (hit == topHit) { continue; }
                        Get<"Edep">(**topHit) += Get<"Edep">(**hit); // sum
                        if (Get<"TrkID">(**hit) == Get<"TrkID">(**topHit)) {
                            ++nTopHit;
                            Get<"tHit">(**topHit) += Get<"tHit">(**hit); // mean
                            *Get<"x">(**topHit) += *Get<"x">(**hit);     // mean
                        }
                    }
                    Get<"tHit">(**topHit) /= nTopHit; // mean
                    *Get<"x">(**topHit) /= nTopHit;   // mean
                    fHitsCollection->insert(topHit->release());
                    // reset
                    hitCandidate.clear();
                    if (timeWindowClosed) {
                        hitCandidate.emplace_back(&aSplitHit);
                        windowClosingTime = Get<"t">(*aSplitHit) + timeResolutionFWHM;
                    }
                }
            }
            splitHit.clear();
        } break;
        }
    }
}

} // namespace MACE::inline Simulation::inline SD
