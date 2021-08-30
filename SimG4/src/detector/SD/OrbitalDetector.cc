#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"

#include "detector/SD/OrbitalDetector.hh"

using namespace MACE::SimG4::SD;
using namespace MACE::SimG4::Hit;

OrbitalDetector::OrbitalDetector(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr) {
    collectionName.insert(hitsCollectionName);
    if (OrbitalDetectorHitAllocator == nullptr) {
        OrbitalDetectorHitAllocator = new G4Allocator<OrbitalDetectorHit>();
    }
}

OrbitalDetector::~OrbitalDetector() {}

void OrbitalDetector::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new OrbitalDetectorHitsCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool OrbitalDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetCurrentStepNumber() > 1 &&
        step->GetTrack()->GetDefinition()->GetPDGCharge() != 0)) {
        return false;
    }
    fHitsCollection->insert(
        new OrbitalDetectorHit(
            step->GetTrack()->GetTrackID(),
            step->GetTrack()->GetGlobalTime() - step->GetTrack()->GetLocalTime(),
            step->GetTrack()->GetVertexPosition(),
            step->GetPreStepPoint()->GetGlobalTime(),
            step->GetPreStepPoint()->GetPosition()
        )
    );
    return true;
}

void OrbitalDetector::EndOfEvent(G4HCofThisEvent*) {}
