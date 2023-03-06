#include "MACE/SimTarget/Action/SteppingAction.hxx"
#include "MACE/SimTarget/Messenger/ActionMessenger.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIdirectory.hh"

namespace MACE::SimTarget::Messenger {

ActionMessenger::ActionMessenger() :
    Singleton(),
    fSteppingAction(nullptr),
    fDirectory(),
    fSetKillIrrelevants() {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Action/");

    fSetKillIrrelevants = std::make_unique<G4UIcmdWithABool>("/MACE/Action/SetKillIrrelevants", this);
    fSetKillIrrelevants->SetGuidance("Kill decay products of muon and muonium for better performance.");
    fSetKillIrrelevants->SetParameterName("b", false);
    fSetKillIrrelevants->AvailableForStates(G4State_Idle);
}

ActionMessenger::~ActionMessenger() = default;

void ActionMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == fSetKillIrrelevants.get()) {
        fSteppingAction->SetKillIrrelevants(fSetKillIrrelevants->GetNewBoolValue(value));
    }
}

} // namespace MACE::SimTarget::Messenger
