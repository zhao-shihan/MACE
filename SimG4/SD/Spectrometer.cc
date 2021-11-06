#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"

#include "SimG4/SD/Spectrometer.hh"
#include "SimG4/Analysis.hh"

using namespace MACE::SimG4;

SD::Spectrometer::Spectrometer(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr) {
    collectionName.insert(hitsCollectionName);
    if (Hit::SpectrometerHitAllocator == nullptr) {
        Hit::SpectrometerHitAllocator = new G4Allocator<Hit::SpectrometerHit>();
    }
}

SD::Spectrometer::~Spectrometer() {}

void SD::Spectrometer::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new Hit::SpectrometerHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool SD::Spectrometer::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (!(step->IsFirstStepInVolume() && track->GetCurrentStepNumber() > 1 &&
        particle->GetPDGCharge() != 0)) {
        return false;
    }
    const auto* const preStepPoint = step->GetPreStepPoint();
    auto* const hit = new Hit::SpectrometerHit();
    hit->SetHitTime(preStepPoint->GetGlobalTime());
    hit->SetHitPosition(preStepPoint->GetPosition());
    hit->SetChamberID(preStepPoint->GetTouchable()->GetCopyNumber());
    hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
    hit->SetVertexPosition(track->GetVertexPosition());
    hit->SetPDGCode(particle->GetPDGEncoding());
    hit->SetTrackID(track->GetTrackID());
    fHitsCollection->insert(hit);
    return true;
}

void SD::Spectrometer::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitSpectrometerHC(fHitsCollection->GetVector());
}
