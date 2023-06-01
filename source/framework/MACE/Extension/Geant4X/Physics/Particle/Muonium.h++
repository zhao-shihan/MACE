#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4ParticleDefinition.hh"

namespace MACE::inline Extension::Geant4X::Physics::inline Particle {

class Muonium final : public Env::Memory::Singleton<Muonium>,
                      public G4ParticleDefinition {
    friend Env::Memory::SingletonFactory;

private:
    Muonium();

public:
    static auto Definition() { return &Instance(); }
};

} // namespace MACE::inline Extension::Geant4X::Physics::inline Particle
