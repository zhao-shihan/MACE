#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Simulation/SD/EMCSD.h++"

#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4ParticleDefinition.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

#include <algorithm>
#include <cmath>
#include <string_view>
#include <utility>

namespace MACE::inline Simulation::inline SD {

EMCSD::EMCSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fEventID{-1},
    fSplitHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
}

auto EMCSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new EMCHitCollection(SensitiveDetectorName, collectionName[0]);
    const auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto EMCSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle == G4OpticalPhoton::Definition()) { return false; }

    const auto eDep{step.GetTotalEnergyDeposit()};

    if (eDep == 0) { return false; }
    assert(eDep > 0);

    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto& touchable{*preStepPoint.GetTouchable()};
    const auto unitID{touchable.GetReplicaNumber()};
    // calculate (Ek0, p0)
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // assert event ID
    assert(fEventID >= 0);
    // new a hit
    auto hit{std::make_unique_for_overwrite<EMCHit>()};
    Get<"EvtID">(*hit) = fEventID;
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"UnitID">(*hit) = unitID;
    Get<"t">(*hit) = preStepPoint.GetGlobalTime();
    Get<"Edep">(*hit) = step.GetTotalEnergyDeposit();
    Get<"Ek">(*hit) = preStepPoint.GetKineticEnergy();
    Get<"x">(*hit) = *touchable.GetRotation() * (preStepPoint.GetPosition() - touchable.GetTranslation());
    Get<"p">(*hit) = preStepPoint.GetMomentum();
    Get<"TrkID">(*hit) = track.GetTrackID();
    Get<"PDGID">(*hit) = particle.GetPDGEncoding();
    Get<"t0">(*hit) = track.GetGlobalTime() - track.GetLocalTime();
    Get<"x0">(*hit) = track.GetVertexPosition();
    Get<"Ek0">(*hit) = vertexEk;
    Get<"p0">(*hit) = vertexMomentum;
    *Get<"CreatProc">(*hit) = creatorProcess ? std::string_view{creatorProcess->GetProcessName()} : "<0>";
    fSplitHit[unitID].emplace_back(std::move(hit));

    return true;
}

auto EMCSD::EndOfEvent(G4HCofThisEvent*) -> void {
    const auto scintillationTimeConstant1{Detector::Description::EMC::Instance().ScintillationTimeConstant1()};
    for (int hitID{};
         auto&& [unitID, splitHit] : fSplitHit) {
        switch (splitHit.size()) {
        case 0:
            break;
        case 1: {
            auto& hit{splitHit.front()};
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"UnitID">(*hit) == unitID);
            fHitsCollection->insert(hit.release());
            splitHit.clear();
        } break;
        default: {
            // sort hit by time
            std::ranges::sort(splitHit,
                              [](const auto& hit1, const auto& hit2) {
                                  return Get<"t">(*hit1) < Get<"t">(*hit2);
                              });
            // loop over all hits on this crystal and cluster to real hits by times
            auto windowClosingTime{Get<"t">(*splitHit.front()) + scintillationTimeConstant1};
            std::vector<std::unique_ptr<EMCHit>*> hitCandidate;
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
                    assert(Get<"UnitID">(**topHit) == unitID);
                    for (auto&& hit : std::as_const(hitCandidate)) {
                        if (hit == topHit) { continue; }
                        Get<"Edep">(**topHit) += Get<"Edep">(**hit);
                    }
                    fHitsCollection->insert(topHit->release());
                    // reset
                    hitCandidate.clear();
                    if (timeWindowClosed) {
                        hitCandidate.emplace_back(&aSplitHit);
                        windowClosingTime = Get<"t">(*aSplitHit) + scintillationTimeConstant1;
                    }
                }
            }
            splitHit.clear();
        } break;
        }
    }
}

} // namespace MACE::inline Simulation::inline SD
