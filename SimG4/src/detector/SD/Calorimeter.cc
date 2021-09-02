#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Gamma.hh"
#include "g4analysis.hh"

#include "detector/SD/Calorimeter.hh"
#include "Analysis.hh"

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
    const auto* const track = step->GetTrack();
    const auto* const preStepPoint = step->GetPreStepPoint();
    if (!(step->IsFirstStepInVolume() && track->GetCurrentStepNumber() > 1 &&
        (track->GetDefinition()->GetPDGCharge() != 0 || track->GetDefinition() == G4Gamma::Definition()) &&
        preStepPoint->GetKineticEnergy() > 461 * keV && preStepPoint->GetKineticEnergy() < 561 * keV)) {
        return false;
    }
    fHitsCollection->insert(
        new CalorimeterHit(
            track->GetTrackID(),
            preStepPoint->GetGlobalTime(),
            preStepPoint->GetKineticEnergy()
        )
    );
    return true;
}

void Calorimeter::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitCalorimeterHC(fHitsCollection);
}
