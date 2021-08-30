#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Gamma.hh"

#include "detector/SD/Calorimeter.hh"

using namespace MACE::SimG4::SD;
using namespace MACE::SimG4::Hit;

Calorimeter::Calorimeter(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr) {
    collectionName.insert(hitsCollectionName);
    if (CalorimeterHitAllocator == nullptr) {
        CalorimeterHitAllocator = new G4Allocator<CalorimeterHit>();
    }
}

Calorimeter::~Calorimeter() {}

void Calorimeter::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new CalorimeterHitsCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool Calorimeter::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetCurrentStepNumber() > 1 &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0 || step->GetTrack()->GetDefinition() == G4Gamma::Definition()) &&
        step->GetPreStepPoint()->GetKineticEnergy() > 461 * keV &&
        step->GetPreStepPoint()->GetKineticEnergy() < 561 * keV)) {
        return false;
    }
    fHitsCollection->insert(
        new CalorimeterHit(
            step->GetTrack()->GetTrackID(),
            step->GetPreStepPoint()->GetGlobalTime(),
            step->GetPreStepPoint()->GetPosition()
        )
    );
    return true;
}

void Calorimeter::EndOfEvent(G4HCofThisEvent*) {}
