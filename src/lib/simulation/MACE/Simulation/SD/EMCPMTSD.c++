#include "MACE/Simulation/SD/EMCPMTSD.h++"
#include "MACE/Utility/PhysicalConstant.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"

#include <cassert>

namespace MACE::inline Simulation::inline SD {

using namespace PhysicalConstant;

EMCPMTSD::EMCPMTSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
}

auto EMCPMTSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHit.clear(); // clear at the begin of event allows EMCSD to get optical photon counts at the end of event

    fHitsCollection = new EMCPMTHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto EMCPMTSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle != G4OpticalPhoton::Definition()) { return false; }

    step.GetTrack()->SetTrackStatus(fStopAndKill);

    const auto postStepPoint{*step.GetPostStepPoint()};
    const auto unitID{postStepPoint.GetTouchable()->GetReplicaNumber()};
    // new a hit
    const auto& hit{fHit[unitID].emplace_back(std::make_unique_for_overwrite<EMCPMTHit>())};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"UnitID">(*hit) = unitID;
    Get<"t">(*hit) = postStepPoint.GetGlobalTime();
    Get<"lambda">(*hit) = h_Planck * c_light / postStepPoint.GetKineticEnergy();
    // Get<"EMCHitID">(*hit) = -1; // to be determined

    return true;
}

auto EMCPMTSD::EndOfEvent(G4HCofThisEvent*) -> void {
    for (int hitID{};
         auto&& [unitID, hitOfUnit] : fHit) {
        for (auto&& hit : hitOfUnit) {
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"UnitID">(*hit) == unitID);
            fHitsCollection->insert(hit.release());
        }
    }
}

auto EMCPMTSD::NOpticalPhotonHit() const -> std::unordered_map<int, int> {
    std::unordered_map<int, int> nHit;
    for (auto&& [unitID, hit] : fHit) {
        if (hit.size() > 0) {
            nHit[unitID] = hit.size();
        }
    }
    return nHit;
}

} // namespace MACE::inline Simulation::inline SD
