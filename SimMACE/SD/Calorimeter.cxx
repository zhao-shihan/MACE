#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4Gamma.hh"

#include "SimMACE/SD/Calorimeter.hxx"
#include "SimMACE/Analysis.hxx"

using namespace MACE::SimMACE;

SD::Calorimeter::Calorimeter(const G4String& SDName, const G4String& hitsCollectionName) :
    G4VSensitiveDetector(SDName),
    fHitsCollection(nullptr) {
    collectionName.insert(hitsCollectionName);
    if (Hit::CalorimeterHitAllocator == nullptr) {
        Hit::CalorimeterHitAllocator = new G4Allocator<Hit::CalorimeterHit>();
    }
}

SD::Calorimeter::~Calorimeter() {}

const G4ParticleDefinition* photon = nullptr;

void SD::Calorimeter::Initialize(G4HCofThisEvent* hitsCollectionOfThisEvent) {
    fHitsCollection = new Hit::CalorimeterHitCollection(SensitiveDetectorName, collectionName[0]);
    auto hitsCollectionID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    hitsCollectionOfThisEvent->AddHitsCollection(hitsCollectionID, fHitsCollection);
    photon = G4Gamma::Definition();
}

G4bool SD::Calorimeter::ProcessHits(G4Step* step, G4TouchableHistory*) {
    const auto* const track = step->GetTrack();
    const auto* const preStepPoint = step->GetPreStepPoint();
    const auto* const particle = track->GetDefinition();
    if (!(step->IsFirstStepInVolume() && track->GetCurrentStepNumber() > 1 &&
        (particle->GetPDGCharge() != 0 || particle == photon))) {
        return false;
    }
    auto* const hit = new Hit::CalorimeterHit();
    hit->SetHitTime(preStepPoint->GetGlobalTime());
    hit->SetEnergy(preStepPoint->GetKineticEnergy());
    hit->SetPDGCode(particle->GetPDGEncoding());
    hit->SetTrackID(track->GetTrackID());
    fHitsCollection->insert(hit);
    return true;
}

void SD::Calorimeter::EndOfEvent(G4HCofThisEvent*) {
    Analysis::Instance()->SubmitCalorimeterHC(fHitsCollection->GetVector());
}
