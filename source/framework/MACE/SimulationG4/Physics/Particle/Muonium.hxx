#pragma once

#include "MACE/Environment/Resource/Singleton.hxx"

#include "G4ParticleDefinition.hh"

namespace MACE::SimulationG4::Physics::Particle {

class Muonium final : public Environment::Resource::Singleton<Muonium>,
                      public G4ParticleDefinition {
    friend Environment::Resource::SingletonFactory;

private:
    Muonium();

public:
    ~Muonium() = default;

    static auto Definition() { return std::addressof(Instance()); }
};

} // namespace MACE::Simulation::Physics::Particle
