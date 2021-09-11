#include "action/ActionInitialization.hh"
#include "action/EventAction.hh"
#include "action/PrimaryGeneratorAction.hh"
#include "action/RunAction.hh"
// #include "action/SteppingAction.hh"

using namespace MACE::SimG4;

ActionInitialization::ActionInitialization() :
    G4VUserActionInitialization() {}

void ActionInitialization::Build() const {
    SetUserAction(new EventAction());
    auto* primaryGeneratorAction = new PrimaryGeneratorAction();
    SetUserAction(primaryGeneratorAction);
    SetUserAction(new RunAction(primaryGeneratorAction));
    // SetUserAction(new SteppingAction());
}

