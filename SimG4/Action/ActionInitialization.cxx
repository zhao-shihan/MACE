#include "SimG4/Action/ActionInitialization.hxx"
#include "SimG4/Action/EventAction.hxx"
#include "SimG4/Action/PrimaryGeneratorAction.hxx"
#include "SimG4/Action/RunAction.hxx"

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

