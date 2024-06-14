#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/Extension/Geant4X/Generator/GeneralParticleSourceX.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimTarget::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    auto NParticlePerEvent() const -> auto { return fGPSX.GetNumberOfParticles(); }

    auto GeneratePrimaries(G4Event* event) -> void override { fGPSX.GeneratePrimaryVertex(event); }

private:
    Geant4X::GeneralParticleSourceX fGPSX;
};

} // namespace MACE::SimTarget::inline Action
