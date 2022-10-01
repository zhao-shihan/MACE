#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4ParticleDefinition.hh"

#include <memory>

namespace MACE::Geant4X::Physics::Particle {

class AntiMuonium final : public Env::Memory::Singleton<AntiMuonium>,
                          public G4ParticleDefinition {
    friend Env::Memory::SingletonFactory;

private:
    AntiMuonium();

public:
    ~AntiMuonium() = default;

    static auto Definition() { return std::addressof(Instance()); }
};

} // namespace MACE::Geant4X::Physics::Particle
