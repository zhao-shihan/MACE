#pragma once

#include "G4VPhysicsConstructor.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Physics::MuoniumPhysics final :
    public G4VPhysicsConstructor {
public:
    MuoniumPhysics(G4int verbose = 1);
    ~MuoniumPhysics() noexcept = default;

    void ConstructParticle() override;
    void ConstructProcess() override;

private:
    G4int fVerbose;
};