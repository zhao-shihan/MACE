#include "MACE/SimVeto/Action/ActionInitialization.h++"
#include "MACE/SimVeto/Action/EventAction.h++"
#include "MACE/SimVeto/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimVeto/Action/RunAction.h++"
#include "MACE/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace MACE::SimVeto::inline Action {

auto ActionInitialization::Build() const -> void {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction);
    SetUserAction(new EventAction);
    SetUserAction(new NeutrinoKillerSteppingAction<>);
}

} // namespace MACE::SimVeto::inline Action
