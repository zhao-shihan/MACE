#pragma once

#include "MACE/Environment/Resource/Singleton.hxx"

#include "G4ParticleDefinition.hh"

namespace MACE::SimulationG4::Physics::Particle {

class AntiMuonium final : public Environment::Resource::Singleton<AntiMuonium>,
                          public G4ParticleDefinition {
    friend Environment::Resource::SingletonFactory;

private:
    AntiMuonium();

public:
    ~AntiMuonium() = default;

    static auto Definition() { return std::addressof(Instance()); }
};

} // namespace MACE::SimulationG4::Physics::Particle
