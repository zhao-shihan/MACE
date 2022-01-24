#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"

#include "SimMACE/SD/OrbitalDetector.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE;

SD::OrbitalDetector::OrbitalDetector(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr) {
    collectionName.insert(hitsCollectionName);
    if (Hit::OrbitalDetectorAllocator == nullptr) {
        Hit::OrbitalDetectorAllocator = new G4Allocator<Hit::OrbitalDetectorHit>();
    }
}

SD::OrbitalDetector::~OrbitalDetector() {}

void SD::OrbitalDetector::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new Hit::OrbitalDetectorHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool SD::OrbitalDetector::ProcessHits(G4Step* step, G4TouchableHistory*) {
    auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (!(step->IsFirstStepInVolume() && track->GetCurrentStepNumber() > 1 &&
        particle->GetPDGCharge() != 0)) {
        return false;
    }
    const auto* const preStepPoint = step->GetPreStepPoint();
    const auto& detectorPosition = preStepPoint->GetTouchable()->GetTranslation();
    const auto* const detectorRotation = preStepPoint->GetTouchable()->GetRotation();
    auto* const hit = new Hit::OrbitalDetectorHit();
    hit->SetHitTime(preStepPoint->GetGlobalTime());
    hit->SetHitPosition((*detectorRotation) * (preStepPoint->GetPosition() - detectorPosition));
    hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
    hit->SetVertexPosition(track->GetVertexPosition());
    hit->SetPDGCode(particle->GetPDGEncoding());
    hit->SetTrackID(track->GetTrackID());
    fHitsCollection->insert(hit);
    return true;
}

void SD::OrbitalDetector::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitOrbitalDetectorHC(fHitsCollection->GetVector());
}
