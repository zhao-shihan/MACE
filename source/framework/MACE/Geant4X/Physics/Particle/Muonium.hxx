#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4ParticleDefinition.hh"

namespace MACE::Geant4X::Physics::Particle {

class Muonium final : public Env::Memory::Singleton<Muonium>,
                      public G4ParticleDefinition {
    friend Env::Memory::SingletonFactory;

private:
    Muonium();

public:
    static auto Definition() { return &Instance(); }
};

} // namespace MACE::Geant4X::Physics::Particle
