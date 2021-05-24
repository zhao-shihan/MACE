#include "SD/PSIMACECsISD.hh"

#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "PSIMACEAnalysisManager.hh"

G4ThreadLocal std::vector<PSIMACECsIHit> PSIMACECsISD::fCsIHitList = std::vector<PSIMACECsIHit>();

PSIMACECsISD::PSIMACECsISD(const G4String& name) :
    G4VSensitiveDetector(name) {
    fCsIHitList.reserve(1000);
}

PSIMACECsISD::~PSIMACECsISD() {}

void PSIMACECsISD::Initialize(G4HCofThisEvent*) {
    fCsIHitList.clear();
}

G4bool PSIMACECsISD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetCurrentStepNumber() > 1 &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0 ||
            step->GetTrack()->GetDefinition() == G4Gamma::Definition()) &&
        step->GetPreStepPoint()->GetKineticEnergy() > 461 * CLHEP::keV &&
        step->GetPreStepPoint()->GetKineticEnergy() < 561 * CLHEP::keV)) {
        return false;
    }
    fCsIHitList.push_back(
        PSIMACECsIHit(
            step->GetTrack()->GetGlobalTime(),
            step->GetPreStepPoint()->GetKineticEnergy()
        )
    );
    return true;
}

void PSIMACECsISD::EndOfEvent(G4HCofThisEvent*) {
    PSIMACEAnalysisManager::ThreadLocalInstance().SubmitCsIHitList(&fCsIHitList);
}
