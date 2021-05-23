#include "SD/PSIMACEMCPSD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Positron.hh"
#include "G4Ions.hh"
#include "G4ios.hh"

#include "PSIMACEConfigs.hh"
#include "PSIMACEAnalysisManager.hh"

G4ThreadLocal std::vector<std::array<G4double, 3>> PSIMACEMCPSD::fMCPHitList = std::vector<std::array<G4double, 3>>();

PSIMACEMCPSD::PSIMACEMCPSD(const G4String& name) :
    G4VSensitiveDetector(name),
    fAnalysisManager(PSIMACEAnalysisManager::Instance()) {
    fMCPHitList.reserve(1000);
}

PSIMACEMCPSD::~PSIMACEMCPSD() {}

void PSIMACEMCPSD::Initialize(G4HCofThisEvent*) {}

G4bool PSIMACEMCPSD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    //     G4ParticleDefinition* particleType = step->GetTrack()->GetDefinition();
    // #if PSIMACE_EXPERIMENT_TYPE == 1
    //     if (!(step->IsFirstStepInVolume() && particleType == G4Electron::Definition() &&
    //         step->GetTotalEnergyDeposit() > 0.))
    // #elif PSIMACE_EXPERIMENT_TYPE == -1
    //     if (!(step->IsFirstStepInVolume() && particleType == G4Positron::Definition()))
    // #else
    // #error "unknown experiment."
    // #endif
    //     {
    //         return false;
    //     }
    if (!(step->GetTrack()->GetParticleDefinition() == G4Positron::Definition() &&
        step->IsFirstStepInVolume() &&
        step->GetTotalEnergyDeposit() > 0)) {
        return false;
    }
    fMCPHitList.push_back(
        {
            step->GetTrack()->GetGlobalTime(),
            -step->GetPostStepPoint()->GetPosition().y() + 830.0 * CLHEP::mm,
            -step->GetPostStepPoint()->GetPosition().z()
        }
    );
    return true;
}

void PSIMACEMCPSD::EndOfEvent(G4HCofThisEvent*) {
    fAnalysisManager->WriteMCPHitList(fMCPHitList);
}
