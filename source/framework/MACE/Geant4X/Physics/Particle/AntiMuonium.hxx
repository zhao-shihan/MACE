#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"

#include "G4ParticleDefinition.hh"

#include <memory>

namespace MACE::Geant4X::Physics::Particle {

class AntiMuonium final : public Environment::Memory::Singleton<AntiMuonium>,
                          public G4ParticleDefinition {
    friend Environment::Memory::SingletonFactory;

private:
    AntiMuonium();

public:
    ~AntiMuonium() = default;

    static auto Definition() { return std::addressof(Instance()); }
};

} // namespace MACE::Geant4X::Physics::Particle
