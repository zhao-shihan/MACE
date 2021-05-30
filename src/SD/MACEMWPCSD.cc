#include "SD/MACEMWPCSD.hh"

#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"

#include "MACEAnalysisManager.hh"

G4ThreadLocal std::vector<MACEMWPCHit> MACEMWPCSD::fMWPCHitList = std::vector<MACEMWPCHit>();

MACEMWPCSD::MACEMWPCSD(const G4String& name) :
    G4VSensitiveDetector(name) {
    fMWPCHitList.reserve(1000);
}

MACEMWPCSD::~MACEMWPCSD() {}

void MACEMWPCSD::Initialize(G4HCofThisEvent*) {
    fMWPCHitList.clear();
}

G4bool MACEMWPCSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetCurrentStepNumber() > 1 &&
        (step->GetTrack()->GetDefinition()->GetPDGCharge() != 0 ||
            step->GetTrack()->GetDefinition() == G4Gamma::Definition()) &&
        step->GetTrack()->GetKineticEnergy() > 1. * CLHEP::keV)) {
        return false;
    }
    fMWPCHitList.push_back(
        MACEMWPCHit(
            step->GetTrack()->GetGlobalTime(),
            step->GetPreStepPoint()->GetPosition().x(),
            step->GetPreStepPoint()->GetPosition().y(),
            step->GetPreStepPoint()->GetPosition().z(),
            step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo()
        )
    );
    return true;
}

void MACEMWPCSD::EndOfEvent(G4HCofThisEvent*) {
    MACEAnalysisManager::ThreadLocalInstance().SubmitMWPCHitList(&fMWPCHitList);
}
