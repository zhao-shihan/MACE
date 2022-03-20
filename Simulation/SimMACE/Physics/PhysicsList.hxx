#pragma once

#include "G4VModularPhysicsList.hh"

#include "SimMACE/Global.hxx"
#include "SimMACE/RunManager.hxx"

class MACE::SimMACE::Physics::PhysicsList final :
    public G4VModularPhysicsList {
    friend RunManager;

private:
    PhysicsList();
    ~PhysicsList() noexcept = default;

public:
    PhysicsList(const PhysicsList&) = delete;
    PhysicsList& operator=(const PhysicsList&) = delete;
};
