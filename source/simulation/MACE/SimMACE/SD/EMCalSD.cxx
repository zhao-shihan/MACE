#include "MACE/SimMACE/RunManager.hxx"
#include "MACE/SimMACE/SD/EMCalSD.hxx"

#include "G4Gamma.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

namespace MACE::SimMACE::inline SD {

EMCalSD::EMCalSD(const G4String& sdName) :
    NonMoveableBase(),
    G4VSensitiveDetector(sdName),
    fEventID(-1),
    fHitsCollection(nullptr) {
    collectionName.insert(sdName + "HC");
}

void EMCalSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new EMCalHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool EMCalSD::ProcessHits(G4Step* theStep, G4TouchableHistory*) {
    const auto& step = *theStep;
    const auto& track = *step.GetTrack();
    const auto& particle = *track.GetDefinition();
    if (step.IsFirstStepInVolume() and track.GetCurrentStepNumber() > 1 and     // is coming from outside, and
        (particle.GetPDGCharge() != 0 or &particle == G4Gamma::Definition())) { // is a charged particle or gamma
        const auto& preStepPoint = *step.GetPreStepPoint();
        // new a hit
        const auto hit = new EMCalHit;
        hit->HitTime(preStepPoint.GetGlobalTime());
        hit->Energy(preStepPoint.GetKineticEnergy());
        hit->Particle(particle.GetParticleName());
        hit->G4EventID(fEventID);
        hit->G4TrackID(track.GetTrackID());
        fHitsCollection->insert(hit);
        return true;
    }
    return false;
}

void EMCalSD::EndOfEvent(G4HCofThisEvent*) {
    RunManager::Instance().GetAnalysis().SubmitEMCalHC(fHitsCollection->GetVector());
}

} // namespace MACE::SimMACE::inline SD
