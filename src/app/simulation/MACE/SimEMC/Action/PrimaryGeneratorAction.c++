#include "MACE/SimEMC/Action/PrimaryGeneratorAction.h++"
#include "MACE/SimEMC/Messenger/PrimaryGeneratorActionMessenger.h++"
#include "MACE/Simulation/Generator/EcoMugCosmicRayMuon.h++"

namespace MACE::SimEMC::inline Action {

PrimaryGeneratorAction::PrimaryGeneratorAction() :
    PassiveSingleton{},
    G4VUserPrimaryGeneratorAction{},
    fGPS{},
    fCosmicRayMuon{},
    fPrimaryType{} {
    PrimaryGeneratorActionMessenger::Instance().AssignTo(this);
}

auto PrimaryGeneratorAction::GeneratePrimaries(G4Event* event) -> void {
    switch (fPrimaryType) {
    case PrimaryType::GPS:
        fGPS.GeneratePrimaryVertex(event);
        break;
    case PrimaryType::CosmicRayMuon:
        fCosmicRayMuon.GeneratePrimaryVertex(event);
        break;
    }
}

} // namespace MACE::SimEMC::inline Action
