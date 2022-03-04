#include "SimMACE/Action/ActionInitialization.hxx"
#include "SimMACE/Action/RunAction.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Action/EventAction.hxx"

using namespace MACE::SimMACE::Action;

void ActionInitialization::Build() const {
    SetUserAction(new RunAction());
    SetUserAction(new PrimaryGeneratorAction());
    SetUserAction(new EventAction());
}
