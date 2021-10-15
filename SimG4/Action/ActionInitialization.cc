#include "SimG4/Action/ActionInitialization.hh"
#include "SimG4/Action/EventAction.hh"
#include "SimG4/Action/PrimaryGeneratorAction.hh"
#include "SimG4/Action/RunAction.hh"

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

