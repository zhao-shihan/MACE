#include "MACE/Simulation/SimTarget/Action/ActionInitialization.hxx"
#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimTarget/Action/RunAction.hxx"
#include "MACE/Simulation/SimTarget/Action/TrackingAction.hxx"

namespace MACE::Simulation::SimTarget::Action {

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new RunAction());
    SetUserAction(new TrackingAction());
}

} // namespace MACE::Simulation::SimTarget
