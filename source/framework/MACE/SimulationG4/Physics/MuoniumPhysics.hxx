#pragma once

#include "G4VPhysicsConstructor.hh"

namespace MACE::SimulationG4::Physics {

class MuoniumPhysics final : public G4VPhysicsConstructor {
public:
    MuoniumPhysics(G4int verbose = 1);
    ~MuoniumPhysics() noexcept = default;
    MuoniumPhysics(const MuoniumPhysics&) = delete;
    MuoniumPhysics& operator=(const MuoniumPhysics&) = delete;

    void ConstructParticle() override;
    void ConstructProcess() override;
};

} // namespace MACE::SimulationG4::Physics
