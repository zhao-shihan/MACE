#pragma once

#include "G4ParticleDefinition.hh"

namespace MACE::Simulation::Physics::Particle {

class Muonium final : public G4ParticleDefinition {
public:
    static Muonium* Definition();
    ~Muonium() noexcept = default;

private:
    Muonium();
    Muonium(const Muonium&) = delete;
    Muonium& operator=(const Muonium&) = delete;

private:
    static Muonium* fgInstance;
};

} // namespace MACE::Simulation::Physics::Particle
