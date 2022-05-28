#include "MACE/Simulation/SimMACE/Analysis.hxx"
#include "MACE/Simulation/SimMACE/RunManager.hxx"
#include "MACE/Simulation/SimMACE/SD/EMCalSD.hxx"

#include "G4Gamma.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

namespace MACE::Simulation::SimMACE::SD {

using Hit::EMCalHit;

EMCalSD::EMCalSD(const G4String& sdName) :
    G4VSensitiveDetector(sdName),
    fHitsCollection(nullptr) {
    collectionName.insert(sdName + "HC");
}

void EMCalSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new EMCalHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool EMCalSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (step->IsFirstStepInVolume() and track->GetCurrentStepNumber() > 1 and   // is coming from outside, and
        (particle->GetPDGCharge() != 0 or particle == G4Gamma::Definition())) { // is a charged particle or gamma
        const auto* const preStepPoint = step->GetPreStepPoint();
        // new a hit
        auto* const hit = new EMCalHit();
        hit->SetHitTime(preStepPoint->GetGlobalTime());
        hit->SetEnergy(preStepPoint->GetKineticEnergy());
        hit->SetParticle(particle->GetParticleName());
        hit->SetG4EventID(fEventID);
        hit->SetG4TrackID(track->GetTrackID());
        fHitsCollection->insert(hit);
        return true;
    } else {
        return false;
    }
}

void EMCalSD::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance().SubmitEMCalHC(fHitsCollection->GetVector());
}

} // namespace MACE::Simulation::SimMACE::SD
