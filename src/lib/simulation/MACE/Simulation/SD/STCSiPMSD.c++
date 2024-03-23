#include "MACE/Simulation/SD/STCSiPMSD.h++"

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

STCSiPMSD::STCSiPMSD(const G4String& sdName) :
    NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
}

auto STCSiPMSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHit.clear(); // clear at the begin of event allows STCSD to get optical photon counts at the end of event

    fHitsCollection = new STCSiPMHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto STCSiPMSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle != G4OpticalPhoton::Definition()) { return false; }

    step.GetTrack()->SetTrackStatus(fStopAndKill);

    const auto postStepPoint{*step.GetPostStepPoint()};
    const auto detectorID{postStepPoint.GetTouchable()->GetReplicaNumber()};
    // new a hit
    auto hit{std::make_unique_for_overwrite<STCSiPMHit>()};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"DetID">(*hit) = detectorID;
    Get<"t">(*hit) = postStepPoint.GetGlobalTime();
    // Get<"STCHitID">(*hit) = -1; // to be determined
    fHit[detectorID].emplace_back(std::move(hit));

    return true;
}

auto STCSiPMSD::EndOfEvent(G4HCofThisEvent*) -> void {
    for (int hitID{};
         auto&& [detectorID, hitOfDetector] : fHit) {
        for (auto&& hit : hitOfDetector) {
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"DetID">(*hit) == detectorID);
            fHitsCollection->insert(hit.release());
        }
    }
}

auto STCSiPMSD::NOpticalPhotonHit() const -> std::unordered_map<int, int> {
    std::unordered_map<int, int> nHit;
    for (auto&& [detectorID, hit] : fHit) {
        if (hit.size() > 0) {
            nHit[detectorID] = hit.size();
        }
    }
    return nHit;
}

} // namespace MACE::Simulation::inline SD
