#include "MACE/SimMMS/Action/PrimaryGeneratorAction.h++"

namespace MACE::SimMMS::inline Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{},
    fAvailableGenerator{},
    fGenerator{&fAvailableGenerator.gpsx},
    fMessengerRegister{this} {}

} // namespace MACE::SimMMS::inline Action
