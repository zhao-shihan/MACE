#include "action/ActionInitialization.hh"
#include "action/EventAction.hh"
#include "action/PrimaryGeneratorAction.hh"
#include "action/RunAction.hh"

using namespace MACE::SimG4;

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

