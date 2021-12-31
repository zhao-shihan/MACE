#pragma once

#include "G4VModularPhysicsList.hh"

#include "SimG4/Global.hxx"

class MACE::SimG4::Physics::PhysicsList : public G4VModularPhysicsList  {
public:
    PhysicsList(G4int verbose = 1);
    virtual ~PhysicsList() {}

    PhysicsList(const PhysicsList&) = delete;
    PhysicsList& operator=(const PhysicsList&) = delete;

private:
    G4int fVerbose;
};
