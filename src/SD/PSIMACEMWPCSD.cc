#include "SD/PSIMACEMWPCSD.hh"

#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "PSIMACEAnalysisManager.hh"

G4ThreadLocal std::vector<PSIMACEMWPCHit> PSIMACEMWPCSD::fMWPCHitList = std::vector<PSIMACEMWPCHit>();

PSIMACEMWPCSD::PSIMACEMWPCSD(const G4String& name) :
    G4VSensitiveDetector(name) {
    fMWPCHitList.reserve(1000);
}

PSIMACEMWPCSD::~PSIMACEMWPCSD() {}

void PSIMACEMWPCSD::Initialize(G4HCofThisEvent*) {
    fMWPCHitList.clear();
}

G4bool PSIMACEMWPCSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetCurrentStepNumber() > 1 &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0 ||
            step->GetTrack()->GetDefinition() == G4Gamma::Definition()) &&
        step->GetTrack()->GetKineticEnergy() > 1. * CLHEP::keV)) {
        return false;
    }
    fMWPCHitList.push_back(
        PSIMACEMWPCHit(
            step->GetTrack()->GetGlobalTime(),
            step->GetPreStepPoint()->GetPosition().x(),
            step->GetPreStepPoint()->GetPosition().y(),
            step->GetPreStepPoint()->GetPosition().z(),
            step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo()
        )
    );
    return true;
}

void PSIMACEMWPCSD::EndOfEvent(G4HCofThisEvent*) {
    PSIMACEAnalysisManager::ThreadLocalInstance().SubmitMWPCHitList(&fMWPCHitList);
}
