#include "userAction/PSIMACEActionInitialization.hh"
#include "userAction/PSIMACEPrimaryGeneratorAction.hh"
#include "userAction/PSIMACERunAction.hh"
#include "userAction/PSIMACEEventAction.hh"
#include "userAction/PSIMACESteppingAction.hh"

PSIMACEActionInitialization::PSIMACEActionInitialization()
    : G4VUserActionInitialization() {}

PSIMACEActionInitialization::~PSIMACEActionInitialization() {}

void PSIMACEActionInitialization::BuildForMaster() const {
    SetUserAction(new PSIMACERunAction());
}

void PSIMACEActionInitialization::Build() const {
    SetUserAction(new PSIMACEPrimaryGeneratorAction);
    SetUserAction(new PSIMACEEventAction);
    SetUserAction(new PSIMACERunAction());
    SetUserAction(new PSIMACESteppingAction());
}

