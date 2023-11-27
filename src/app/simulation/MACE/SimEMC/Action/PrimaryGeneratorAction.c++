#include "MACE/SimEMC/Action/PrimaryGeneratorAction.h++"
// #include "MACE/SimEMC/Messenger/PrimaryGeneratorActionMessenger.h++"

namespace MACE::SimEMC::inline Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{},
    fGPS{} {
    // PrimaryGeneratorActionMessenger::Instance().AssignTo(this);
    fGPS = new G4GeneralParticleSource();
}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    fGPS->GeneratePrimaryVertex(event);
}

} // namespace MACE::SimEMC::inline Action
