#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"

#include "G4ParticleDefinition.hh"

#include <memory>

namespace MACE::Geant4X::Physics::Particle {

class Muonium final : public Environment::Memory::Singleton<Muonium>,
                      public G4ParticleDefinition {
    friend Environment::Memory::SingletonFactory;

private:
    Muonium();

public:
    ~Muonium() = default;

    static auto Definition() { return std::addressof(Instance()); }
};

} // namespace MACE::Geant4X::Physics::Particle
