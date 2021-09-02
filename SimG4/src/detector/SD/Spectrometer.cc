#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"

#include "detector/SD/Spectrometer.hh"
#include "Analysis.hh"

using namespace MACE::SimG4::SD;
using namespace MACE::SimG4::Hit;

Spectrometer::Spectrometer(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr) {
    collectionName.insert(hitsCollectionName);
    if (SpectrometerHitAllocator == nullptr) {
        SpectrometerHitAllocator = new G4Allocator<SpectrometerHit>();
    }
}

Spectrometer::~Spectrometer() {}

void Spectrometer::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new SpectrometerHitsCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool Spectrometer::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* const track = step->GetTrack();
    if (!(step->IsFirstStepInVolume() && track->GetCurrentStepNumber() > 1 &&
        track->GetDefinition()->GetPDGCharge() != 0)) {
        return false;
    }
    const auto* const preStepPoint = step->GetPreStepPoint();
    fHitsCollection->insert(
        new SpectrometerHit(
            track->GetTrackID(),
            preStepPoint->GetTouchable()->GetCopyNumber(),
            track->GetGlobalTime() - track->GetLocalTime(),
            track->GetVertexPosition(),
            preStepPoint->GetGlobalTime(),
            preStepPoint->GetPosition()
        )
    );
    return true;
}

void Spectrometer::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitSpectrometerHC(fHitsCollection);
}
