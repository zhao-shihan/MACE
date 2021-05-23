#include "SD/PSIMACEMWPCSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Ions.hh"
#include "G4ios.hh"

#include "PSIMACEConfigs.hh"

G4ThreadLocal std::vector<std::pair<std::array<G4double, 4>, G4int>> PSIMACEMWPCSD::fMagSpecHitList = std::vector<std::pair<std::array<G4double, 4>, G4int>>();

PSIMACEMWPCSD::PSIMACEMWPCSD(const G4String& name) :
    G4VSensitiveDetector(name),
    fAnalysisManager(PSIMACEAnalysisManager::Instance()) {
    fMagSpecHitList.reserve(1000);
}

PSIMACEMWPCSD::~PSIMACEMWPCSD() {}

void PSIMACEMWPCSD::Initialize(G4HCofThisEvent*) {}

G4bool PSIMACEMWPCSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    // #if PSIMACE_EXPERIMENT_TYPE == 1
    //     if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetDefinition() == G4Positron::Definition()))
    // #elif PSIMACE_EXPERIMENT_TYPE == -1
    //     if (!(step->IsFirstStepInVolume() && step->GetTrack()->GetDefinition() == G4Electron::Definition() &&
    //         step->GetTotalEnergyDeposit() > 0.))
    // #else
    // #error "unknown experiment."
    // #endif
    //     {
    //         return false;
    //     }
    if (!(step->GetTrack()->GetParticleDefinition() == G4Electron::Definition() &&
        step->IsFirstStepInVolume() &&
        step->GetTrack()->GetKineticEnergy() > 10 * CLHEP::keV &&
        step->GetTotalEnergyDeposit() > 0)) {
        return false;
    }
    fMagSpecHitList.push_back(
        std::make_pair(
            std::array<G4double, 4>{step->GetTrack()->GetGlobalTime(),
            step->GetPreStepPoint()->GetPosition().x(),
            step->GetPreStepPoint()->GetPosition().y() + 418.0 * CLHEP::mm,
            -step->GetPreStepPoint()->GetPosition().z()},
            step->GetPreStepPoint()->GetPhysicalVolume()->GetCopyNo()
        )
    );
    return true;
}

void PSIMACEMWPCSD::EndOfEvent(G4HCofThisEvent*) {
    fAnalysisManager->WriteMWPCHitList(fMagSpecHitList);
}
