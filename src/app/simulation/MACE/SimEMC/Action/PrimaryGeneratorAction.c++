#include "MACE/SimEMC/Action/PrimaryGeneratorAction.h++"

namespace MACE::SimEMC::inline Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{},
    fAvailableGenerator{},
    fGenerator{&fAvailableGenerator.gps},
    fMessengerRegister{this} {}

} // namespace MACE::SimEMC::inline Action
