#include "MACE/SimTarget/Action/SteppingAction.hxx"
#include "MACE/SimTarget/Messenger/ActionMessenger.hxx"

namespace MACE::SimTarget::Messenger {

ActionMessenger::ActionMessenger() :
    Environment::Resource::Singleton<ActionMessenger>(),
    fSteppingAction(nullptr),
    fDirectory("/MACE/Action/"),
    fSetKillIrrelevants("/MACE/Action/SetKillIrrelevants", this) {

    fSetKillIrrelevants.SetGuidance("Kill decay products of muon and muonium for better performance.");
    fSetKillIrrelevants.SetParameterName("b", false);
    fSetKillIrrelevants.AvailableForStates(G4State_Idle);
}

void ActionMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetKillIrrelevants)) {
        fSteppingAction->SetKillIrrelevants(fSetKillIrrelevants.GetNewBoolValue(value));
    }
}

} // namespace MACE::SimTarget::Messenger
