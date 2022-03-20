#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include "SimMACE/RunManager.hxx"
#include "SimMACE/SD/VertexDetectorSD.hxx"
#include "SimMACE/Utility/Analysis.hxx"

using namespace MACE::SimMACE::SD;

VertexDetectorSD::VertexDetectorSD(const G4String& sdName) :
    G4VSensitiveDetector(sdName),
    fHitsCollection(nullptr) {
    collectionName.insert(sdName + "HC");
}

void VertexDetectorSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new VertexDetectorHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool VertexDetectorSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (step->IsFirstStepInVolume() and track->GetCurrentStepNumber() > 1 and  // is coming from outside, and
        particle->GetPDGCharge() != 0) {                                       // is a charged particle.
        const auto* const preStepPoint = step->GetPreStepPoint();
        const auto* const touchable = preStepPoint->GetTouchable();
        // get detector transform
        const auto& detectorPosition = touchable->GetTranslation();
        const auto& detectorRotation = *touchable->GetRotation();
        // transform hit position to local coordinate
        const auto hitPosition = G4TwoVector(detectorRotation * (preStepPoint->GetPosition() - detectorPosition));
        // new a hit
        auto* const hit = new VertexDetectorHit();
        hit->SetHitTime(preStepPoint->GetGlobalTime());
        hit->SetHitPosition(hitPosition);
        hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
        hit->SetVertexPosition(track->GetVertexPosition());
        hit->SetParticleName(particle->GetParticleName());
        hit->SetEventID(fEventID);
        hit->SetTrackID(track->GetTrackID());
        fHitsCollection->insert(hit);
        return true;
    } else {
        return false;
    }
}

void VertexDetectorSD::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance().SubmitVertexDetectorHC(fHitsCollection->GetVector());
}
