#pragma once

#include "G4ParticleDefinition.hh"

namespace MACE::Simulation::Physics::Particle {

class AntiMuonium final : public G4ParticleDefinition {
public:
    static AntiMuonium* Definition();
    ~AntiMuonium() noexcept = default;

private:
    AntiMuonium();
    AntiMuonium(const AntiMuonium&) = delete;
    AntiMuonium& operator=(const AntiMuonium&) = delete;

private:
    static AntiMuonium* fgInstance;
};

} // namespace MACE::Simulation::Physics::Particle
