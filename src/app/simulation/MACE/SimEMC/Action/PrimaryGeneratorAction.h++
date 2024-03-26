#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Extension/Geant4X/GeneralParticleSourceX.h++"
#include "MACE/SimEMC/Messenger/PrimaryGeneratorActionMessenger.h++"
#include "MACE/Simulation/Generator/EcoMugCosmicRayMuon.h++"

#include "G4VPrimaryGenerator.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimEMC::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    PrimaryGeneratorAction();

    auto SwitchToGPSX() -> void { fGenerator = &fAvailableGenerator.gpsx; }
    auto SwitchToEcoMug() -> void { fGenerator = &fAvailableGenerator.ecoMug; }

    auto GeneratePrimaries(G4Event* event) -> void override { fGenerator->GeneratePrimaryVertex(event); }

private:
    struct {
        Geant4X::GeneralParticleSourceX gpsx;
        Generator::EcoMugCosmicRayMuon ecoMug;
    } fAvailableGenerator;
    G4VPrimaryGenerator* fGenerator;

    PrimaryGeneratorActionMessenger::Register<PrimaryGeneratorAction> fMessengerRegister;
};

} // namespace MACE::SimEMC::inline Action
