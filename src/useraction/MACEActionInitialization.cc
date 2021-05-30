#include "useraction/MACEActionInitialization.hh"
#include "useraction/MACEPrimaryGeneratorAction.hh"
#include "useraction/MACERunAction.hh"
#include "useraction/MACEEventAction.hh"
#include "useraction/MACESteppingAction.hh"

MACEActionInitialization::MACEActionInitialization()
    : G4VUserActionInitialization() {}

MACEActionInitialization::~MACEActionInitialization() {}

void MACEActionInitialization::BuildForMaster() const {
    SetUserAction(new MACERunAction());
}

void MACEActionInitialization::Build() const {
    SetUserAction(new MACEPrimaryGeneratorAction);
    SetUserAction(new MACEEventAction);
    SetUserAction(new MACERunAction());
    SetUserAction(new MACESteppingAction());
}

