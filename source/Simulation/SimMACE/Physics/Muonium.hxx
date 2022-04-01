#pragma once

#include "Simulation/SimMACE/Global.hxx"

#include "G4ParticleDefinition.hh"

namespace MACE::Simulation::SimMACE::Physics {

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

} // namespace MACE::Simulation::SimMACE::Physics
