#include "MACE/Simulation/SimMACE/Action/ActionInitialization.h++"
#include "MACE/Simulation/SimMACE/Action/EventAction.h++"
#include "MACE/Simulation/SimMACE/Action/PrimaryGeneratorAction.h++"
#include "MACE/Simulation/SimMACE/Action/RunAction.h++"

namespace MACE::inline Simulation::SimMACE {

void ActionInitialization::Build() const {
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new EventAction);
}

} // namespace MACE::inline Simulation::SimMACE
