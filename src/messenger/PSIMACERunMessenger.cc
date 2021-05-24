#include "messenger/PSIMACERunMessenger.hh"
#include "userAction/PSIMACERunAction.hh"
#include "PSIMACEAnalysisManager.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

PSIMACERunMessenger::PSIMACERunMessenger(PSIMACERunAction* run) :
    G4UImessenger(),
    fRunAction(run) {
    fDirectory = new G4UIdirectory("/PSIMACERun/");
    fDirectory->SetGuidance("User Run Action control.");

    fRootcmd = new G4UIcmdWithAString("/PSIMACERun/SetFileName", this);
    fRootcmd->SetGuidance("Set root file name.");
    fRootcmd->SetParameterName("rfilename", false);
    fRootcmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

PSIMACERunMessenger::~PSIMACERunMessenger() {
    delete fRootcmd;
}

void PSIMACERunMessenger::SetNewValue(G4UIcommand* command, G4String newvalue) {
    if (command == fRootcmd) {
        PSIMACEAnalysisManager::SetFileName(newvalue);
    }
}


