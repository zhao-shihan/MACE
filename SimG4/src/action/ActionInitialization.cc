#include "action/ActionInitialization.hh"
#include "action/PrimaryGeneratorAction.hh"
#include "action/RunAction.hh"
// #include "useraction/MACEEventAction.hh"
// #include "useraction/MACESteppingAction.hh"

using namespace MACE::SimG4;

ActionInitialization::ActionInitialization() :
    G4VUserActionInitialization() {}

void ActionInitialization::Build() const {
    SetUserAction(new PrimaryGeneratorAction);
    // SetUserAction(new MACEEventAction);
    SetUserAction(new RunAction());
    // SetUserAction(new MACESteppingAction());
}

