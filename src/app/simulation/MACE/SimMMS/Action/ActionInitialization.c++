#include "MACE/SimMMS/Action/ActionInitialization.h++"
#include "MACE/SimMMS/Action/EventAction.h++"
#include "MACE/SimMMS/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimMMS/Action/RunAction.h++"
#include "MACE/SimMMS/Action/TrackingAction.h++"
#include "MACE/Simulation/Action/NeutrinoKillerSteppingAction.h++"

namespace MACE::SimMMS {

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

} // namespace MACE::SimMMS
