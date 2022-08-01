#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"

#include "G4ParticleDefinition.hh"

namespace MACE::SimulationG4::Physics::Particle {

class Muonium final : public Environment::Memory::Singleton<Muonium>,
                      public G4ParticleDefinition {
    friend Environment::Memory::SingletonFactory;

private:
    Muonium();

public:
    ~Muonium() = default;

    static auto Definition() { return std::addressof(Instance()); }
};

} // namespace MACE::SimulationG4::Physics::Particle
