#pragma once

#include "FTFP_BERT.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Physics::PhysicsList : public FTFP_BERT {
public:
    PhysicsList(G4int verbose = 1);
    virtual ~PhysicsList() {}

    PhysicsList(const PhysicsList&) = delete;
    PhysicsList& operator=(const PhysicsList&) = delete;

private:
    G4int fVerbose;
};
