#include "messenger/MACERunMessenger.hh"
#include "useraction/MACERunAction.hh"
#include "MACEAnalysisManager.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"

MACERunMessenger::MACERunMessenger(MACERunAction* run) :
    G4UImessenger(),
    fRunAction(run) {
    fDirectory = new G4UIdirectory("/MACERun/");
    fDirectory->SetGuidance("User Run Action control.");

    fRootcmd = new G4UIcmdWithAString("/MACERun/SetFileName", this);
    fRootcmd->SetGuidance("Set root file name.");
    fRootcmd->SetParameterName("rfilename", false);
    fRootcmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

MACERunMessenger::~MACERunMessenger() {
    delete fRootcmd;
}

void MACERunMessenger::SetNewValue(G4UIcommand* command, G4String newvalue) {
    if (command == fRootcmd) {
        MACEAnalysisManager::SetFileName(newvalue);
    }
}


