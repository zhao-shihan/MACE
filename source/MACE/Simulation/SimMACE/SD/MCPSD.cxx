#include "MACE/Simulation/SimMACE/Analysis.hxx"
#include "MACE/Simulation/SimMACE/RunManager.hxx"
#include "MACE/Simulation/SimMACE/SD/MCPSD.hxx"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

namespace MACE::Simulation::SimMACE::SD {

using Hit::MCPHit;

MCPSD::MCPSD(const G4String& sdName) :
    G4VSensitiveDetector(sdName),
    fEventID(-1),
    fHitsCollection(nullptr) {
    collectionName.insert(sdName + "HC");
}

void MCPSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new MCPHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool MCPSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (step->IsFirstStepInVolume() and track->GetCurrentStepNumber() > 1 and // is coming from outside, and
        particle->GetPDGCharge() != 0) {                                      // is a charged particle.
        const auto* const preStepPoint = step->GetPreStepPoint();
        const auto* const touchable = preStepPoint->GetTouchable();
        // get detector transform
        const auto& detectorPosition = touchable->GetTranslation();
        const auto& detectorRotation = *touchable->GetRotation();
        // transform hit position to local coordinate
        const auto hitPosition = G4TwoVector(detectorRotation * (preStepPoint->GetPosition() - detectorPosition));
        // new a hit
        auto* const hit = new MCPHit();
        hit->SetHitTime(preStepPoint->GetGlobalTime());
        hit->SetHitPosition(hitPosition);
        hit->SetVertexTime(track->GetGlobalTime() - track->GetLocalTime());
        hit->SetVertexPosition(track->GetVertexPosition());
        hit->SetParticle(particle->GetParticleName());
        hit->SetG4EventID(fEventID);
        hit->SetG4TrackID(track->GetTrackID());
        fHitsCollection->insert(hit);
        return true;
    } else {
        return false;
    }
}

void MCPSD::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance().SubmitMCPHC(fHitsCollection->GetVector());
}

} // namespace MACE::Simulation::SimMACE::SD
