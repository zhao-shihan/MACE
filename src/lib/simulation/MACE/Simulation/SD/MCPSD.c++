#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Env/Print.h++"
#include "MACE/External/gfx/timsort.hpp"
#include "MACE/Simulation/SD/MCPSD.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4ParticleDefinition.hh"
#include "G4RotationMatrix.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4ThreeVector.hh"
#include "G4TwoVector.hh"
#include "G4VProcess.hh"
#include "G4VTouchable.hh"

#include <cassert>
#include <cmath>
#include <ranges>
#include <string_view>

namespace MACE::inline Simulation::inline SD {

using namespace LiteralUnit::Energy;

MCPSD::MCPSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fIonizingEnergyDepositionThreshold{20_eV},
    fSplitHit{},
    fHitsCollection{},
    fMessengerRegister{this} {
    collectionName.insert(sdName + "HC");
}

auto MCPSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new MCPHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto MCPSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto eDep{step.GetTotalEnergyDeposit()};

    assert(0 <= step.GetNonIonizingEnergyDeposit());
    assert(step.GetNonIonizingEnergyDeposit() <= eDep);
    if (eDep - step.GetNonIonizingEnergyDeposit() < fIonizingEnergyDepositionThreshold) { return false; }

    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};
    const auto& preStepPoint{*step.GetPreStepPoint()};
    const auto& touchable{*preStepPoint.GetTouchable()};
    // transform hit position to local coordinate
    const G4TwoVector hitPosition{*touchable.GetRotation() * (preStepPoint.GetPosition() - touchable.GetTranslation())};
    // calculate (E0, p0)
    const auto vertexEk{track.GetVertexKineticEnergy()};
    const auto vertexMomentum{track.GetVertexMomentumDirection() * std::sqrt(vertexEk * (vertexEk + 2 * particle.GetPDGMass()))};
    // track creator process
    const auto creatorProcess{track.GetCreatorProcess()};
    // new a hit
    const auto& hit{fSplitHit.emplace_back(std::make_unique_for_overwrite<MCPHit>())};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"t">(*hit) = preStepPoint.GetGlobalTime();
    Get<"x">(*hit) = hitPosition;
    Get<"Edep">(*hit) = eDep;
    Get<"Ek">(*hit) = preStepPoint.GetKineticEnergy();
    Get<"p">(*hit) = preStepPoint.GetMomentum();
    Get<"TrkID">(*hit) = track.GetTrackID();
    Get<"PDGID">(*hit) = particle.GetPDGEncoding();
    Get<"t0">(*hit) = track.GetGlobalTime() - track.GetLocalTime();
    Get<"x0">(*hit) = track.GetVertexPosition();
    Get<"Ek0">(*hit) = vertexEk;
    Get<"p0">(*hit) = vertexMomentum;
    *Get<"CreatProc">(*hit) = creatorProcess ? std::string_view{creatorProcess->GetProcessName()} : "|0>";

    return true;
}

auto MCPSD::EndOfEvent(G4HCofThisEvent*) -> void {
    switch (fSplitHit.size()) {
    case 0:
        break;
    case 1: {
        auto& hit{fSplitHit.front()};
        Get<"HitID">(*hit) = 0;
        fHitsCollection->insert(hit.release());
    } break;
    default: {
        const auto timeResolutionFWHM{Detector::Description::MCP::Instance().TimeResolutionFWHM()};
        assert(timeResolutionFWHM >= 0);
        int hitID{};
        // sort hit by time
        gfx::timsort(fSplitHit,
                     [](const auto& hit1, const auto& hit2) {
                         return Get<"t">(*hit1) < Get<"t">(*hit2);
                     });
        // loop over all hits and cluster to real hits by times
        auto clusterFirst{fSplitHit.begin()};
        auto clusterLast{clusterFirst};
        do {
            const auto tFirst{*Get<"t">(**clusterFirst)};
            const auto windowClosingTime{tFirst + timeResolutionFWHM};
            if (tFirst == windowClosingTime and // Notice: bad numeric with huge Get<"t">(**clusterFirst)!
                timeResolutionFWHM != 0) [[unlikely]] {
                Env::PrintLnWarning("Warning: A huge time ({}) completely rounds off the time resolution ({})", tFirst, timeResolutionFWHM);
            }
            clusterLast = std::ranges::find_if_not(clusterFirst, fSplitHit.end(),
                                                   [&windowClosingTime](const auto& hit) {
                                                       return Get<"t">(*hit) <= windowClosingTime;
                                                   });
            // find top hit
            auto& topHit{*std::ranges::min_element(clusterFirst, clusterLast,
                                                   [](const auto& hit1, const auto& hit2) {
                                                       return Get<"TrkID">(*hit1) < Get<"TrkID">(*hit2);
                                                   })};
            // construct real hit
            Get<"HitID">(*topHit) = hitID++;
            for (const auto& hit : std::ranges::subrange{clusterFirst, clusterLast}) {
                if (hit == topHit) { continue; }
                Get<"Edep">(*topHit) += Get<"Edep">(*hit);
            }
            fHitsCollection->insert(topHit.release());
            clusterFirst = clusterLast;
        } while (clusterFirst != fSplitHit.end());
    } break;
    }
    fSplitHit.clear();
}

} // namespace MACE::inline Simulation::inline SD
