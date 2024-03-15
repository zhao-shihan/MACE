#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimEMC/Messenger/PrimaryGeneratorActionMessenger.h++"
#include "MACE/Simulation/Generator/EcoMugCosmicRayMuon.h++"

#include "G4GeneralParticleSource.hh"
#include "G4VPrimaryGenerator.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimEMC::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto SwitchToGPS() -> void { fGenerator = &fAvailableGenerator.gps; }
    auto SwitchToEcoMug() -> void { fGenerator = &fAvailableGenerator.ecoMug; }

    auto GeneratePrimaries(G4Event* event) -> void override { fGenerator->GeneratePrimaryVertex(event); }

private:
    struct {
        G4GeneralParticleSource gps;
        Generator::EcoMugCosmicRayMuon ecoMug;
    } fAvailableGenerator;
    G4VPrimaryGenerator* fGenerator;

    PrimaryGeneratorActionMessenger::Register<PrimaryGeneratorAction> fMessengerRegister;
};

} // namespace MACE::SimEMC::inline Action
