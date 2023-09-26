#include "MACE/SimEMC/Action/PrimaryGeneratorAction.h++"
// #include "MACE/SimEMC/Messenger/PrimaryGeneratorActionMessenger.h++"

namespace MACE::SimEMC::inline Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{} {
    // PrimaryGeneratorActionMessenger::Instance().AssignTo(this);
}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
}

} // namespace MACE::SimEMC::inline Action
