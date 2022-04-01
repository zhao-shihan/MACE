#pragma once

#include "Simulation/SimMACE/Global.hxx"

#include "G4VPhysicsConstructor.hh"

namespace MACE::Simulation::SimMACE::Physics {

class MuoniumPhysics final : public G4VPhysicsConstructor {
public:
    MuoniumPhysics(G4int verbose = 1);
    ~MuoniumPhysics() noexcept = default;

    void ConstructParticle() override;
    void ConstructProcess() override;

private:
    G4int fVerbose;
};

} // namespace MACE::Simulation::SimMACE::Physics
