#include "MACE/Simulation/SD/ECALPMTSD.h++"

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

ECALPMTSD::ECALPMTSD(const G4String& sdName) :
    Mustard::NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
}

auto ECALPMTSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHit.clear(); // clear at the begin of event allows ECALSD to get optical photon counts at the end of event

    fHitsCollection = new ECALPMTHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto ECALPMTSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle != G4OpticalPhoton::Definition()) { return false; }

    step.GetTrack()->SetTrackStatus(fStopAndKill);

    const auto postStepPoint{*step.GetPostStepPoint()};
    const auto modID{postStepPoint.GetTouchable()->GetReplicaNumber()};
    // new a hit
    const auto& hit{fHit[modID].emplace_back(std::make_unique_for_overwrite<ECALPMTHit>())};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"ModID">(*hit) = modID;
    Get<"t">(*hit) = postStepPoint.GetGlobalTime();

    return true;
}

auto ECALPMTSD::EndOfEvent(G4HCofThisEvent*) -> void {
    for (int hitID{};
         auto&& [modID, hitOfUnit] : fHit) {
        for (auto&& hit : hitOfUnit) {
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"ModID">(*hit) == modID);
            fHitsCollection->insert(hit.release());
        }
    }
}

auto ECALPMTSD::NOpticalPhotonHit() const -> std::unordered_map<int, int> {
    std::unordered_map<int, int> nHit;
    for (auto&& [modID, hit] : fHit) {
        if (hit.size() > 0) {
            nHit[modID] = hit.size();
        }
    }
    return nHit;
}

} // namespace MACE::inline Simulation::inline SD
