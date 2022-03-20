#include "G4Gamma.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4Step.hh"

#include "SimMACE/RunManager.hxx"
#include "SimMACE/SD/CalorimeterSD.hxx"
#include "SimMACE/Utility/Analysis.hxx"

using namespace MACE::SimMACE::SD;

CalorimeterSD::CalorimeterSD(const G4String& sdName) :
    G4VSensitiveDetector(sdName),
    fHitsCollection(nullptr) {
    collectionName.insert(sdName + "HC");
}

void CalorimeterSD::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new CalorimeterHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
}

G4bool CalorimeterSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* const track = step->GetTrack();
    const auto* const particle = track->GetDefinition();
    if (step->IsFirstStepInVolume() and track->GetCurrentStepNumber() > 1 and    // is coming from outside, and
        (particle->GetPDGCharge() != 0 or particle == G4Gamma::Definition())) {  // is a charged particle or gamma
        const auto* const preStepPoint = step->GetPreStepPoint();
        // new a hit
        auto* const hit = new CalorimeterHit();
        hit->SetHitTime(preStepPoint->GetGlobalTime());
        hit->SetEnergy(preStepPoint->GetKineticEnergy());
        hit->SetParticleName(particle->GetParticleName());
        hit->SetEventID(fEventID);
        hit->SetTrackID(track->GetTrackID());
        fHitsCollection->insert(hit);
        return true;
    } else {
        return false;
    }
}

void CalorimeterSD::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance().SubmitCalorimeterHC(fHitsCollection->GetVector());
}
