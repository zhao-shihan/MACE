#include "MACE/SimEMC/Action/PrimaryGeneratorAction.h++"
// #include "MACE/SimEMC/Messenger/PrimaryGeneratorActionMessenger.h++"

namespace MACE::SimEMC::inline Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{},
    fParticleGun{0} {
    // PrimaryGeneratorActionMessenger::Instance().AssignTo(this);
    fParticleGun = new G4GeneralParticleSource();
}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    fParticleGun->GeneratePrimaryVertex(event);
}

} // namespace MACE::SimEMC::inline Action
