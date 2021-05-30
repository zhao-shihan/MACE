#include "SD/MACEMCPSD.hh"

#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "MACEAnalysisManager.hh"

G4ThreadLocal std::vector<MACEMCPHit> MACEMCPSD::fMCPHitList = std::vector<MACEMCPHit>(0);

MACEMCPSD::MACEMCPSD(const G4String& name) :
    G4VSensitiveDetector(name) {
    fMCPHitList.reserve(1000);
}

MACEMCPSD::~MACEMCPSD() {}

void MACEMCPSD::Initialize(G4HCofThisEvent*) {
    fMCPHitList.clear();
}

G4bool MACEMCPSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetCurrentStepNumber() > 1 &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0 ||
            step->GetTrack()->GetDefinition() == G4Gamma::Definition()) &&
        step->GetTrack()->GetKineticEnergy() > 1. * CLHEP::keV)) {
        return false;
    }
    fMCPHitList.push_back(
        MACEMCPHit(
            step->GetTrack()->GetGlobalTime(),
            step->GetPreStepPoint()->GetPosition().y(),
            -(step->GetPreStepPoint()->GetPosition().z() - 1600. * CLHEP::mm)
        )
    );
    return true;
}

void MACEMCPSD::EndOfEvent(G4HCofThisEvent*) {
    MACEAnalysisManager::ThreadLocalInstance().SubmitMCPHitList(&fMCPHitList);
}
