// #include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/SD/PMTSD.h++"

#include "G4HCofThisEvent.hh"
#include "G4OpticalPhoton.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include <utility>

namespace MACE::SimEMC::inline SD {

PMTSD::PMTSD(G4String name) :
    NonMoveableBase{},
    G4VSensitiveDetector{std::move(name)},
    fHitsCollection{nullptr} {
    collectionName.insert(SensitiveDetectorName + "HC");
}

auto PMTSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new PMTHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto PMTSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
    auto particleDefinition = theStep->GetTrack()->GetDefinition();
    if (particleDefinition != G4OpticalPhoton::OpticalPhotonDefinition())
        return false;

    theStep->GetTrack()->SetTrackStatus(fStopAndKill);

    auto hit = new PMTHit;
    auto globalTime = theStep->GetPostStepPoint()->GetGlobalTime();
    auto copyNo = theStep->GetTrack()->GetVolume()->GetCopyNo();
    hit->Time(globalTime);
    hit->CopyNo(copyNo);
    fHitsCollection->insert(hit);

    return true;
}

auto PMTSD::EndOfEvent(G4HCofThisEvent*) -> void {
}

} // namespace MACE::SimEMC::inline SD
