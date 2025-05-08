#include "MACE/SimPTS/Action/ActionInitialization.h++"
#include "MACE/SimPTS/Action/EventAction.h++"
#include "MACE/SimPTS/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimPTS/Action/RunAction.h++"
#include "MACE/SimPTS/Action/TrackingAction.h++"
#include "MACE/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace MACE::SimPTS {

ActionInitialization::ActionInitialization() :
    PassiveSingleton{this},
    G4VUserActionInitialization{} {}

auto ActionInitialization::Build() const -> void {
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new EventAction);
    SetUserAction(new TrackingAction);
    SetUserAction(new NeutrinoKillerSteppingAction<>);
}

} // namespace MACE::SimPTS
