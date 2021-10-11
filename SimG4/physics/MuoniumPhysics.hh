#pragma once

#include "G4VPhysicsConstructor.hh"

#include "SimG4/Global.hh"

class MACE::SimG4::Physics::MuoniumPhysics : public G4VPhysicsConstructor {
public:
    MuoniumPhysics(G4int verbose = 1);

    void ConstructParticle() override;
    void ConstructProcess() override;

private:
    G4int fVerbose;
};