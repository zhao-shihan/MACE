#include "MACE/SimMACE/RunManager.hxx"
#include "MACE/SimMACE/SD/MCPSD.hxx"

#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

namespace MACE::SimMACE::SD {

using Hit::MCPHit;

MCPSD::MCPSD(const G4String& sdName) :
    NonMoveableBase(),
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

G4bool MCPSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) {
    const auto& step = *theStep;
    const auto& track = *step.GetTrack();
    const auto& particle = *track.GetDefinition();
    if (step.IsFirstStepInVolume() and track.GetCurrentStepNumber() > 1 and // is coming from outside, and
        particle.GetPDGCharge() != 0) {                                     // is a charged particle.
        const auto& preStepPoint = *step.GetPreStepPoint();
        const auto& touchable = *preStepPoint.GetTouchable();
        // get detector transform
        const auto& detectorPosition = touchable.GetTranslation();
        const auto& detectorRotation = *touchable.GetRotation();
        // transform hit position to local coordinate
        const auto hitPosition = G4TwoVector(detectorRotation * (preStepPoint.GetPosition() - detectorPosition));
        // new a hit
        const auto hit = new MCPHit;
        hit->HitTime(preStepPoint.GetGlobalTime());
        hit->HitPosition(hitPosition);
        hit->VertexTime(track.GetGlobalTime() - track.GetLocalTime());
        hit->VertexPosition(track.GetVertexPosition());
        hit->Particle(particle.GetParticleName());
        hit->G4EventID(fEventID);
        hit->G4TrackID(track.GetTrackID());
        fHitsCollection->insert(hit);
        return true;
    }
    return false;
}

void MCPSD::EndOfEvent(G4HCofThisEvent*) {
    RunManager::Instance().GetAnalysis().SubmitMCPHC(fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::SD
