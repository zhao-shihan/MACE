#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Simulation/Generator/EcoMugCosmicRayMuon.h++"

#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimEMC::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
private:
    enum class PrimaryType {
        GPS,
        CosmicRayMuon
    };

public:
    PrimaryGeneratorAction();

    auto SwitchToGPS() -> void { fPrimaryType = PrimaryType::GPS; }
    auto SwitchToCosmicRayMuon() -> void { fPrimaryType = PrimaryType::CosmicRayMuon; }

    auto GeneratePrimaries(G4Event* event) -> void override;

private:
    G4GeneralParticleSource fGPS;
    Generator::EcoMugCosmicRayMuon fCosmicRayMuon;

    PrimaryType fPrimaryType;
};

} // namespace MACE::SimEMC::inline Action
