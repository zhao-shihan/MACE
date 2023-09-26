#include "MACE/SimEMC/Analysis.h++"
#include "MACE/SimEMC/SD/SiPMSD.h++"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include <utility>

namespace MACE::SimEMC::inline SD {

SiPMSD::SiPMSD(G4String name) :
    NonMoveableBase{},
    G4VSensitiveDetector{std::move(name)},
    fHitsCollection{nullptr} {
    collectionName.insert(SensitiveDetectorName + "HC");
}

auto SiPMSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) -> void {
    fHitsCollection = new SiPMHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

auto SiPMSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) -> G4bool {
}

auto SiPMSD::EndOfEvent(G4HCofThisEvent*) -> void {
}

} // namespace MACE::SimEMC::inline SD
