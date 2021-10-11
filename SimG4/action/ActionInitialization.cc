#include "SimG4/action/ActionInitialization.hh"
#include "SimG4/action/EventAction.hh"
#include "SimG4/action/PrimaryGeneratorAction.hh"
#include "SimG4/action/RunAction.hh"

using namespace MACE::SimG4::Action;

ActionInitialization::ActionInitialization() :
    G4VUserActionInitialization() {}

void ActionInitialization::Build() const {
    auto primaryGeneratorAction = new PrimaryGeneratorAction();
    auto eventAction = new EventAction();
    auto runAction = new RunAction(primaryGeneratorAction, eventAction);

    SetUserAction(primaryGeneratorAction);
    SetUserAction(eventAction);
    SetUserAction(runAction);
}

