#include "SimMACE/Action/ActionInitialization.hxx"
#include "SimMACE/Action/EventAction.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Action/RunAction.hxx"

using MACE::Simulation::SimMACE::Action::ActionInitialization;

void ActionInitialization::Build() const {
    SetUserAction(new RunAction());
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new EventAction());
}
