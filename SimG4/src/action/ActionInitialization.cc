#include "action/ActionInitialization.hh"
#include "action/EventAction.hh"
#include "action/PrimaryGeneratorAction.hh"
#include "action/RunAction.hh"

using namespace MACE::SimG4;

ActionInitialization::ActionInitialization(const DetectorConstruction* pDetectorConstruction) :
    G4VUserActionInitialization(),
    fpDetectorConstruction(pDetectorConstruction) {}

void ActionInitialization::Build() const {
    auto primaryGeneratorAction = new PrimaryGeneratorAction();
    auto eventAction = new EventAction();
    auto runAction = new RunAction(fpDetectorConstruction, primaryGeneratorAction, eventAction);

    SetUserAction(primaryGeneratorAction);
    SetUserAction(eventAction);
    SetUserAction(runAction);
}

