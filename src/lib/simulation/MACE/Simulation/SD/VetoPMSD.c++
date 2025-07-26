#include "MACE/Detector/Description/PDSVeto.h++"
#include "MACE/Simulation/SD/VetoPMSD.h++"

#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"
#include "G4StepPoint.hh"
#include "G4Track.hh"
#include "G4VTouchable.hh"

#include <algorithm>
#include <cassert>

namespace MACE::inline Simulation::inline SD {
using namespace MACE::Detector::Description;

VetoPMSD::VetoPMSD(const G4String& sdName) :
    // Mustard::NonMoveableBase{},
    G4VSensitiveDetector{sdName},
    fHit{},
    fHitsCollection{} {
    collectionName.insert(sdName + "HC");
}

auto VetoPMSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHit.clear(); // clear at the begin of event allows VetoSD to get optical photon counts at the end of event
    fHitsCollection = new VetoPMHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID{G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection)};
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto VetoPMSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    const auto& step{*theStep};
    const auto& track{*step.GetTrack()};
    const auto& particle{*track.GetDefinition()};

    if (&particle != G4OpticalPhoton::Definition()) { return false; }

    step.GetTrack()->SetTrackStatus(fStopAndKill);

    const auto postStepPoint{*step.GetPostStepPoint()};
    // replica number: 0_cathode, 1_SiPM, 2_StripBox, 3_ModuleBox
    const auto& veto{PDSVeto::Instance()};
    const auto stripID{[&]() {
        const auto stripLocalID{postStepPoint.GetTouchable()->GetReplicaNumber(2)};
        const auto moduleID{postStepPoint.GetTouchable()->GetReplicaNumber(3)};
        return stripLocalID + veto.StartingStripIDOfAModule().at(moduleID);
    }()};
    const auto localSiPMID{postStepPoint.GetTouchable()->GetReplicaNumber(1)};
    // const auto siliconPMID{localSiPMID + stripID};
    // new a hit
    auto hit{std::make_unique_for_overwrite<VetoPMHit>()};
    Get<"EvtID">(*hit) = G4EventManager::GetEventManager()->GetConstCurrentEvent()->GetEventID();
    Get<"HitID">(*hit) = -1; // to be determined
    Get<"StripID">(*hit) = stripID;
    Get<"LocalSiPMID">(*hit) = localSiPMID;
    Get<"t">(*hit) = postStepPoint.GetGlobalTime();
    fHit[stripID].emplace_back(std::move(hit));
    return true;
}

auto VetoPMSD::EndOfEvent(G4HCofThisEvent*) -> void {
    for (int hitID{};
         auto&& [stripID, hitOfUnit] : fHit) {
        for (auto&& hit : hitOfUnit) {
            Get<"HitID">(*hit) = hitID++;
            assert(Get<"StripID">(*hit) == stripID);
            fHitsCollection->insert(hit.release());
            // Notice: One VetoPMHit unique_ptr released, but pointer object remains
        }
    }
}

auto VetoPMSD::NOpticalPhotonHit() const -> std::unordered_map<int, int> {
    std::unordered_map<int, int> nHit;
    for (auto&& [stripID, hit] : fHit) {
        if (hit.size() > 0) {
            nHit[stripID] = hit.size();
        }
    }
    return nHit;
}

auto VetoPMSD::NOpticalPhotonOnEachSiPM() const -> std::unordered_map<int, std::vector<int>> {
    const auto& veto{PDSVeto::Instance()};
    std::unordered_map<int, std::vector<int>> nHitOnEachSiPM;
    for (auto&& [stripID, hitOfUnit] : fHit) {
        if (hitOfUnit.size() > 0) {
            std::vector<int> nHitOnEachSiPMOfThisStrip(veto.FiberNum() * 2, 0);
            for (auto&& aHit : hitOfUnit) {
                auto sipmID {Get<"LocalSiPMID">(*aHit)};
                nHitOnEachSiPMOfThisStrip.at(sipmID)++;
            };
            nHitOnEachSiPM[stripID] = nHitOnEachSiPMOfThisStrip;
        }
    }
    return nHitOnEachSiPM;
}
} // namespace MACE::inline Simulation::inline SD
