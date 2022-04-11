#include "MACE/Simulation/SimTarget/ActionInitialization.hxx"
#include "MACE/Simulation/SimTarget/EventAction.hxx"
#include "MACE/Simulation/SimTarget/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimTarget/RunAction.hxx"

namespace MACE::Simulation::SimTarget {

void ActionInitialization::Build() const {
    SetUserAction(new RunAction());
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new EventAction());
}

} // namespace MACE::Simulation::SimTarget
