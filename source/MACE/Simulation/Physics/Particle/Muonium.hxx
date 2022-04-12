#pragma once

#include "G4ParticleDefinition.hh"

namespace MACE::Simulation::Physics {

// Muonium Definition

class Muonium final : public G4ParticleDefinition {
public:
    static Muonium* Definition();

private:
    static Muonium* fgInstance;

private:
    Muonium();

public:
    ~Muonium() noexcept = default;
};

} // namespace MACE::Simulation::Physics
