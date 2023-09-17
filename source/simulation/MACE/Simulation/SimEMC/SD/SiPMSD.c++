#include "MACE/Simulation/SimEMC/Analysis.h++"
#include "MACE/Simulation/SimEMC/SD/SiPMSD.h++"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

namespace MACE::inline Simulation::SimEMC::inline SD {

SiPMSD::SiPMSD(const G4String& sdName) :
    NonMoveableBase(),
    G4VSensitiveDetector(sdName),
    fEventID(-1),
    fHitsCollection(nullptr) {
    collectionName.insert(sdName + "HC");
}

void SiPMSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new EMCHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool SiPMSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) {
}

void SiPMSD::EndOfEvent(G4HCofThisEvent*) {
}

} // namespace MACE::inline Simulation::SimEMC::inline SD
