#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4ParticleDefinition.hh"

namespace MACE::inline Simulation::inline Physics::inline Particle {

class Muonium final : public Env::Memory::Singleton<Muonium>,
                      public G4ParticleDefinition {
    friend Env::Memory::SingletonFactory;

private:
    Muonium();

public:
    static auto Definition() -> auto { return &Instance(); }
};

} // namespace MACE::inline Simulation::inline Physics::inline Particle
