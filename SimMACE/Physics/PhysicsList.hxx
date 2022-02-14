#pragma once

#include "G4VModularPhysicsList.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Physics::PhysicsList final :
    public G4VModularPhysicsList {
public:
    PhysicsList(G4int verbose = 1);
    virtual ~PhysicsList() noexcept = default;

    PhysicsList(const PhysicsList&) = delete;
    PhysicsList& operator=(const PhysicsList&) = delete;
};
