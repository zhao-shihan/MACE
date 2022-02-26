#include "SimMACE/Action/ActionInitialization.hxx"
#include "SimMACE/Action/EventAction.hxx"
#include "SimMACE/Action/PrimaryGeneratorAction.hxx"
#include "SimMACE/Action/RunAction.hxx"

using namespace MACE::SimMACE::Action;

void ActionInitialization::Build() const {
    auto runAction = new RunAction();
    auto eventAction = new EventAction(runAction);
    auto primaryGeneratorAction = new PrimaryGeneratorAction(eventAction);

    SetUserAction(runAction);
    SetUserAction(eventAction);
    SetUserAction(primaryGeneratorAction);
}
