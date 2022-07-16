#include "MACE/Simulation/SimMACE/Action/ActionInitialization.hxx"
#include "MACE/Simulation/SimMACE/Action/EventAction.hxx"
#include "MACE/Simulation/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Simulation/SimMACE/Action/RunAction.hxx"

using MACE::Simulation::SimMACE::Action::ActionInitialization;

void ActionInitialization::Build() const {
    SetUserAction(new RunAction());
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new EventAction());
}
