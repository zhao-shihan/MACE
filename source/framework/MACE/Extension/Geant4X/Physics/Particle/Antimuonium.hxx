#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4ParticleDefinition.hh"

namespace MACE::inline Extension::Geant4X::Physics::Particle {

class Antimuonium final : public Env::Memory::Singleton<Antimuonium>,
                          public G4ParticleDefinition {
    friend Env::Memory::SingletonFactory;

private:
    Antimuonium();

public:
    static auto Definition() { return &Instance(); }
};

} // namespace MACE::inline Extension::Geant4X::Physics::Particle
