#include "MACE/SimECAL/Action/ActionInitialization.h++"
#include "MACE/SimECAL/Action/EventAction.h++"
#include "MACE/SimECAL/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimECAL/Action/RunAction.h++"
#include "MACE/SimECAL/Action/TrackingAction.h++"
#include "MACE/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace MACE::SimECAL::inline Action {

ActionInitialization::ActionInitialization() :
    PassiveSingleton{this},
    G4VUserActionInitialization{} {}

auto ActionInitialization::Build() const -> void {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new RunAction);
    SetUserAction(new EventAction);
    SetUserAction(new TrackingAction);
    SetUserAction(new NeutrinoKillerSteppingAction<>);
}

} // namespace MACE::SimECAL::inline Action
