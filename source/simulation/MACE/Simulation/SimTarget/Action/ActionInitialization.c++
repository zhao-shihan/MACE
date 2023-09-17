#include "MACE/Simulation/SimTarget/Action/ActionInitialization.h++"
#include "MACE/Simulation/SimTarget/Action/EventAction.h++"
#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.h++"
#include "MACE/Simulation/SimTarget/Action/RunAction.h++"
#include "MACE/Simulation/SimTarget/Action/SteppingAction.h++"
#include "MACE/Simulation/SimTarget/Action/TrackingAction.h++"

namespace MACE::inline Simulation::SimTarget::inline Action {

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new SteppingAction);
    SetUserAction(new TrackingAction);
    SetUserAction(new EventAction);
    SetUserAction(new RunAction);
}

} // namespace MACE::inline Simulation::SimTarget::inline Action
