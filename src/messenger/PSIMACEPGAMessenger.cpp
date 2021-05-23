#include "messenger/PSIMACEPGAMessenger.hh"
#include "userAction/PSIMACEPrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"

PSIMACEPGAMessenger::PSIMACEPGAMessenger(PSIMACEPrimaryGeneratorAction* PGA) :
    G4UImessenger(),
    fPrimaryGeneratorAction(PGA) {
    fDirectory = new G4UIdirectory("/PSIMACESource/");
    fDirectory->SetGuidance("PSIMACE particle Source.");

    fPPECmd = new G4UIcmdWithADouble("/PSIMACESource/SetParticlesPerEvent", this);
    fPPECmd->SetGuidance("Set number of mu+ generate in an event.");
    fPPECmd->SetParameterName("PPE", false);
    fPPECmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

PSIMACEPGAMessenger::~PSIMACEPGAMessenger() {
    delete fPPECmd;
}

void PSIMACEPGAMessenger::SetNewValue(G4UIcommand* command, G4String newvalue) {
    if (command == fPPECmd) {
        fPrimaryGeneratorAction->SetParticlesPerEvent((G4int)fPPECmd->GetNewDoubleValue(newvalue));
    }
}


