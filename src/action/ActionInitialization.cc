#include "action/ActionInitialization.hh"
#include "action/PrimaryGeneratorAction.hh"
// #include "useraction/MACERunAction.hh"
// #include "useraction/MACEEventAction.hh"
// #include "useraction/MACESteppingAction.hh"

MACE::ActionInitialization::ActionInitialization()
    : G4VUserActionInitialization() {}

void MACE::ActionInitialization::Build() const {
    SetUserAction(new MACE::PrimaryGeneratorAction);
    // SetUserAction(new MACEEventAction);
    // SetUserAction(new MACERunAction());
    // SetUserAction(new MACESteppingAction());
}

