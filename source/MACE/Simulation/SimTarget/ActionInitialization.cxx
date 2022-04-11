#include "MACE/Simulation/SimTarget/ActionInitialization.hxx"
#include "MACE/Simulation/SimTarget/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimTarget/RunAction.hxx"
#include "MACE/Simulation/SimTarget/TrackingAction.hxx"

namespace MACE::Simulation::SimTarget {

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new RunAction());
    SetUserAction(new TrackingAction());
}

} // namespace MACE::Simulation::SimTarget
