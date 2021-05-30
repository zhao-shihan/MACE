#include "SD/PSIMACEMCPSD.hh"

#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "PSIMACEAnalysisManager.hh"

G4ThreadLocal std::vector<PSIMACEMCPHit> PSIMACEMCPSD::fMCPHitList = std::vector<PSIMACEMCPHit>(0);

PSIMACEMCPSD::PSIMACEMCPSD(const G4String& name) :
    G4VSensitiveDetector(name) {
    fMCPHitList.reserve(1000);
}

PSIMACEMCPSD::~PSIMACEMCPSD() {}

void PSIMACEMCPSD::Initialize(G4HCofThisEvent*) {
    fMCPHitList.clear();
}

G4bool PSIMACEMCPSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetCurrentStepNumber() > 1 &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0 ||
            step->GetTrack()->GetDefinition() == G4Gamma::Definition()) &&
        step->GetTrack()->GetKineticEnergy() > 1. * CLHEP::keV)) {
        return false;
    }
    fMCPHitList.push_back(
        PSIMACEMCPHit(
            step->GetTrack()->GetGlobalTime(),
            step->GetPreStepPoint()->GetPosition().y(),
            -(step->GetPreStepPoint()->GetPosition().z() - 1600. * CLHEP::mm)
        )
    );
    return true;
}

void PSIMACEMCPSD::EndOfEvent(G4HCofThisEvent*) {
    PSIMACEAnalysisManager::ThreadLocalInstance().SubmitMCPHitList(&fMCPHitList);
}
