#include "action/ActionInitialization.hh"
#include "action/PrimaryGeneratorAction.hh"
// #include "useraction/MACERunAction.hh"
// #include "useraction/MACEEventAction.hh"
// #include "useraction/MACESteppingAction.hh"

MACE::SimG4::ActionInitialization::ActionInitialization()
    : G4VUserActionInitialization() {}

void MACE::SimG4::ActionInitialization::Build() const {
    SetUserAction(new MACE::SimG4::PrimaryGeneratorAction);
    // SetUserAction(new MACEEventAction);
    // SetUserAction(new MACERunAction());
    // SetUserAction(new MACESteppingAction());
}

