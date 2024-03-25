#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4GeneralParticleSource.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

namespace MACE::SimMMS::inline Action {

class PrimaryGeneratorAction final : public Env::Memory::PassiveSingleton<PrimaryGeneratorAction>,
                                     public G4VUserPrimaryGeneratorAction {
public:
    auto GeneratePrimaries(G4Event* event) -> void override { fGeneralParticleSource.GeneratePrimaryVertex(event); }

private:
    G4GeneralParticleSource fGeneralParticleSource;
};

} // namespace MACE::SimMMS::inline Action
