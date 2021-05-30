#include "SD/MACECsISD.hh"

#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "MACEAnalysisManager.hh"

G4ThreadLocal std::vector<MACECsIHit> MACECsISD::fCsIHitList = std::vector<MACECsIHit>();

MACECsISD::MACECsISD(const G4String& name) :
    G4VSensitiveDetector(name) {
    fCsIHitList.reserve(1000);
}

MACECsISD::~MACECsISD() {}

void MACECsISD::Initialize(G4HCofThisEvent*) {
    fCsIHitList.clear();
}

G4bool MACECsISD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetCurrentStepNumber() > 1 &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0 ||
            step->GetTrack()->GetDefinition() == G4Gamma::Definition()) &&
        step->GetPreStepPoint()->GetKineticEnergy() > 461 * CLHEP::keV &&
        step->GetPreStepPoint()->GetKineticEnergy() < 561 * CLHEP::keV)) {
        return false;
    }
    fCsIHitList.push_back(
        MACECsIHit(
            step->GetTrack()->GetGlobalTime(),
            step->GetPreStepPoint()->GetKineticEnergy()
        )
    );
    return true;
}

void MACECsISD::EndOfEvent(G4HCofThisEvent*) {
    MACEAnalysisManager::ThreadLocalInstance().SubmitCsIHitList(&fCsIHitList);
}
