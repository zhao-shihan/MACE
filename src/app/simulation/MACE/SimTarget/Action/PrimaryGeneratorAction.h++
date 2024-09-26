#pragma once

#include "Mustard/Env/Memory/PassiveSingleton.h++"
#include "Mustard/Extension/Geant4X/Generator/GeneralParticleSourceX.h++"

#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimTarget::inline Action {

class PrimaryGeneratorAction final : public Mustard::Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    auto NVertex() const -> auto { return fGPSX.NVertex(); }

    auto GeneratePrimaries(G4Event* event) -> void override { fGPSX.GeneratePrimaryVertex(event); }

private:
    Mustard::Geant4X::GeneralParticleSourceX fGPSX;
};

} // namespace MACE::SimTarget::inline Action
