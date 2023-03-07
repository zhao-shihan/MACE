#include "MACE/SimMACE/Action/ActionInitialization.hxx"
#include "MACE/SimMACE/Action/EventAction.hxx"
#include "MACE/SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "MACE/SimMACE/Action/RunAction.hxx"

using MACE::SimMACE::Action::ActionInitialization;

void ActionInitialization::Build() const {
    SetUserAction(new RunAction);
    SetUserAction(new PrimaryGeneratorAction);
    SetUserAction(new EventAction);
}
