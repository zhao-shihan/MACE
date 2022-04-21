#include "MACE/Simulation/SimTarget/Messenger/ActionMessenger.hxx"

namespace MACE::Simulation::SimTarget::Messenger {

ActionMessenger& ActionMessenger::Instance() {
    static ActionMessenger instance;
    return instance;
}

ActionMessenger::ActionMessenger() :
    fDirectory("/MACE/Action/"),
    fSetKillDecayProducts("/MACE/Action/SetKillDecayProducts", this) {

    fSetKillDecayProducts.SetGuidance("Kill decay products of muon and muonium for better performance.");
    fSetKillDecayProducts.SetParameterName("b", false);
    fSetKillDecayProducts.AvailableForStates(G4State_Idle);
}

void ActionMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    if (command == std::addressof(fSetKillDecayProducts)) {
        fSteppingAction->SetKillDecayProducts(fSetKillDecayProducts.GetNewBoolValue(value));
    }
}

} // namespace MACE::Simulation::SimTarget::Messenger
