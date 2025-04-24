#include "MACE/SimTarget/Action/SteppingAction.h++"
#include "MACE/SimTarget/Messenger/ActionMessenger.h++"

#include "G4UIcmdWithABool.hh"
#include "G4UIdirectory.hh"

namespace MACE::SimTarget::inline Messenger {

ActionMessenger::ActionMessenger() :
    SingletonMessenger{},
    fDirectory{},
    fKillIrrelevance{} {

    fDirectory = std::make_unique<G4UIdirectory>("/MACE/Action/");

    fKillIrrelevance = std::make_unique<G4UIcmdWithABool>("/MACE/Action/KillIrrelevance", this);
    fKillIrrelevance->SetGuidance("Kill decay products of muon and muonium for better performance.");
    fKillIrrelevance->SetParameterName("b", false);
    fKillIrrelevance->AvailableForStates(G4State_Idle);
}

ActionMessenger::~ActionMessenger() = default;

auto ActionMessenger::SetNewValue(G4UIcommand* command, G4String value) -> void {
    if (command == fKillIrrelevance.get()) {
        Deliver<SteppingAction>([&](auto&& r) {
            r.KillIrrelevance(fKillIrrelevance->GetNewBoolValue(value));
        });
    }
}

} // namespace MACE::SimTarget::inline Messenger
