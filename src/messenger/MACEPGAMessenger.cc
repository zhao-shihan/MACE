#include "messenger/MACEPGAMessenger.hh"
#include "useraction/MACEPrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADouble.hh"

MACEPGAMessenger::MACEPGAMessenger(MACEPrimaryGeneratorAction* PGA) :
    G4UImessenger(),
    fPrimaryGeneratorAction(PGA) {
    fDirectory = new G4UIdirectory("/MACESource/");
    fDirectory->SetGuidance("MACE particle Source.");

    fPPECmd = new G4UIcmdWithADouble("/MACESource/SetParticlesPerEvent", this);
    fPPECmd->SetGuidance("Set number of mu+ generate in an event.");
    fPPECmd->SetParameterName("PPE", false);
    fPPECmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

MACEPGAMessenger::~MACEPGAMessenger() {
    delete fPPECmd;
}

void MACEPGAMessenger::SetNewValue(G4UIcommand* command, G4String newvalue) {
    if (command == fPPECmd) {
        fPrimaryGeneratorAction->SetParticlesPerEvent((G4int)fPPECmd->GetNewDoubleValue(newvalue));
    }
}


