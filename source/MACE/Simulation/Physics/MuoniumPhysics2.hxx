#pragma once

#include "G4VPhysicsConstructor.hh"

namespace MACE::Simulation::Physics {

class MuoniumPhysics2 final : public G4VPhysicsConstructor {
public:
    MuoniumPhysics2(G4int verbose = 1);
    ~MuoniumPhysics2() noexcept = default;
    MuoniumPhysics2(const MuoniumPhysics2&) = delete;
    MuoniumPhysics2& operator=(const MuoniumPhysics2&) = delete;

    void ConstructParticle() override;
    void ConstructProcess() override;

private:
    G4int fVerbose;
};

} // namespace MACE::Simulation::Physics
