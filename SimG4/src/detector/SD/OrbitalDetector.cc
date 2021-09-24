#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"

#include "detector/SD/OrbitalDetector.hh"
#include "Analysis.hh"

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
    auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (!(step->IsFirstStepInVolume() && track->GetCurrentStepNumber() > 1 &&
        particle->GetPDGCharge() != 0)) {
        return false;
    }
    const auto* const preStepPoint = step->GetPreStepPoint();
    const auto& detectorPosition = preStepPoint->GetTouchable()->GetTranslation();
    const auto* const detectorRotation = preStepPoint->GetTouchable()->GetRotation();
    fHitsCollection->insert(
        new OrbitalDetectorHit(
            track->GetTrackID(),
            track->GetGlobalTime() - track->GetLocalTime(),
            track->GetVertexPosition(),
            preStepPoint->GetGlobalTime(),
            (*detectorRotation) * (preStepPoint->GetPosition() - detectorPosition),
            particle
        )
    );
    track->SetTrackStatus(fStopAndKill);
    return true;
}

void OrbitalDetector::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitOrbitalDetectorHC(fHitsCollection);
}
