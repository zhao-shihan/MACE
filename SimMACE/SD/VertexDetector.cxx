#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"

#include "SimMACE/SD/VertexDetector.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE;

SD::VertexDetector::VertexDetector(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr) {
    collectionName.insert(hitsCollectionName);
    if (Hit::VertexDetectorAllocator == nullptr) {
        Hit::VertexDetectorAllocator = new G4Allocator<Hit::VertexDetectorHit>();
    }
}

SD::VertexDetector::~VertexDetector() {}

void SD::VertexDetector::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new Hit::VertexDetectorHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool SD::VertexDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (!(step->IsFirstStepInVolume() and track->GetCurrentStepNumber() > 1 and
        particle->GetPDGCharge() != 0)) {
        return false;
    }
    const auto* const preStepPoint = step->GetPreStepPoint();
    const auto& detectorPosition = preStepPoint->GetTouchable()->GetTranslation();
    const auto* const detectorRotation = preStepPoint->GetTouchable()->GetRotation();
    auto* const hit = new Hit::VertexDetectorHit();
    hit->SetHitTime(preStepPoint->GetGlobalTime());
    hit->SetHitPosition((*detectorRotation) * (preStepPoint->GetPosition() - detectorPosition));
    hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
    hit->SetVertexPosition(track->GetVertexPosition());
    hit->SetPDGCode(particle->GetPDGEncoding());
    hit->SetTrackID(track->GetTrackID());
    fHitsCollection->insert(hit);
    return true;
}

void SD::VertexDetector::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitVertexDetectorHC(fHitsCollection->GetVector());
}
