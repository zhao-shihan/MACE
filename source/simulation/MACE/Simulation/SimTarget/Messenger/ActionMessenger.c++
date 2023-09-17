#include "MACE/Simulation/SimTarget/Action/SteppingAction.h++"
#include "MACE/Simulation/SimTarget/Messenger/ActionMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIdirectory.hh"

namespace MACE::inline Simulation::SimTarget::inline Messenger {

ActionMessenger::ActionMessenger() :
    Singleton(),
    fSteppingAction(nullptr),
    fDirectory(),
    fKillIrrelevants() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Action/");

    fKillIrrelevants = std::make_unique<G4UIcmdWithABool>("/MACE/Action/KillIrrelevants", this);
    fKillIrrelevants->SetGuidance("Kill decay products of muon and muonium for better performance.");
    fKillIrrelevants->SetParameterName("b", false);
    fKillIrrelevants->AvailableForStates(G4State_Idle);
}

ActionMessenger::~ActionMessenger() = default;

void ActionMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fKillIrrelevants.get()) {
        fSteppingAction->SetKillIrrelevants(fKillIrrelevants->GetNewBoolValue(value));
    }
}

} // namespace MACE::inline Simulation::SimTarget::inline Messenger
