#pragma once

#include "G4ParticleDefinition.hh"

namespace MACE::Simulation::Physics {

class AntiMuonium final : public G4ParticleDefinition {
public:
    static AntiMuonium* Definition();

private:
    static AntiMuonium* fgInstance;

private:
    AntiMuonium();

public:
    ~AntiMuonium() noexcept = default;
};

} // namespace MACE::Simulation::Physics
