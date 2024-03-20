#include "MACE/Detector/Description/EMC.h++"
#include "MACE/External/gfx/timsort.hpp"
#include "MACE/Simulation/SD/EMCPMTSD.h++"
#include "MACE/Simulation/SD/EMCSD.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
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
#include <cassert>
#include <cmath>
#include <string_view>
#include <utility>

namespace MACE::inline Simulation::inline SD {

EMCSD::EMCSD(const G4String& sdName, const EMCPMTSD* emcPMTSD) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fEMCPMTSD{emcPMTSD},
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
    // new a hit
    auto hit{std::make_unique_for_overwrite<EMCHit>()};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"UnitID">(*hit) = unitID;
    Get<"t">(*hit) = preStepPoint.GetGlobalTime();
    Get<"Edep">(*hit) = step.GetTotalEnergyDeposit();
    Get<"nOptPho">(*hit) = -1; // to be determined
    Get<"Ek">(*hit) = preStepPoint.GetKineticEnergy();
    Get<"x">(*hit) = *touchable.GetRotation() * (preStepPoint.GetPosition() - touchable.GetTranslation());
    Get<"p">(*hit) = preStepPoint.GetMomentum();
    Get<"TrkID">(*hit) = track.GetTrackID();
    Get<"PDGID">(*hit) = particle.GetPDGEncoding();
    Get<"t0">(*hit) = track.GetGlobalTime() - track.GetLocalTime();
    Get<"x0">(*hit) = track.GetVertexPosition();
    Get<"Ek0">(*hit) = vertexEk;
    Get<"p0">(*hit) = vertexMomentum;
    *Get<"CreatProc">(*hit) = creatorProcess ? std::string_view{creatorProcess->GetProcessName()} : "|0>";
    fSplitHit[unitID].emplace_back(std::move(hit));

    return true;
}

auto EMCSD::EndOfEvent(G4HCofThisEvent*) -> void {
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
        } break;
        default: {
            const auto scintillationTimeConstant1{Detector::Description::EMC::Instance().ScintillationTimeConstant1()};
            // sort hit by time
            gfx::timsort(splitHit,
                         [](const auto& hit1, const auto& hit2) {
                             return Get<"t">(*hit1) < Get<"t">(*hit2);
                         });
            // loop over all hits on this crystal and cluster to real hits by times
            std::vector<std::unique_ptr<EMCHit>*> hitCandidate;
            const auto ClusterAndInsertHit{
                [&] {
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
                }};
            for (auto windowClosingTime{Get<"t">(*splitHit.front()) + scintillationTimeConstant1};
                 auto&& aSplitHit : splitHit) {
                if (Get<"t">(*aSplitHit) > windowClosingTime) {
                    ClusterAndInsertHit();
                    hitCandidate.clear();
                    windowClosingTime = Get<"t">(*aSplitHit) + scintillationTimeConstant1;
                }
                hitCandidate.emplace_back(&aSplitHit);
            }
            ClusterAndInsertHit();
        } break;
        }
        splitHit.clear();
    }
    if (fEMCPMTSD != nullptr) {
        auto nHit{fEMCPMTSD->NOpticalPhotonHit()};
        for (auto&& hit : std::as_const(*fHitsCollection->GetVector())) {
            Get<"nOptPho">(*hit) = nHit[Get<"UnitID">(*hit)];
        }
    }
}

} // namespace MACE::inline Simulation::inline SD
