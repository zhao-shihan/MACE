#include "SD/PSIMACECsISD.hh"

#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"

#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4Ions.hh"
#include "G4ios.hh"

G4ThreadLocal std::vector<std::array<G4double, 2>> PSIMACECsISD::fCsIHitList = std::vector<std::array<G4double, 2>>();

PSIMACECsISD::PSIMACECsISD(const G4String& name) :
    G4VSensitiveDetector(name),
    fAnalysisManager(PSIMACEAnalysisManager::Instance()) {
    fCsIHitList.reserve(1000);
}

PSIMACECsISD::~PSIMACECsISD() {}

void PSIMACECsISD::Initialize(G4HCofThisEvent*) {}

G4bool PSIMACECsISD::ProcessHits(G4Step* step, G4TouchableHistory*) {
    if (!(step->GetTrack()->GetParticleDefinition() == G4Gamma::Definition() &&
        step->IsFirstStepInVolume() &&
        step->GetTotalEnergyDeposit() > 0)) {
        return false;
    }
    fCsIHitList.push_back(
        {
            step->GetTrack()->GetGlobalTime(),
            step->GetPreStepPoint()->GetTotalEnergy()
        }
    );
    return true;
}

void PSIMACECsISD::EndOfEvent(G4HCofThisEvent*) {
    fAnalysisManager->WriteCsIHitList(fCsIHitList);
}
