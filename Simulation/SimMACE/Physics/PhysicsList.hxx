#pragma once

#include "Simulation/SimMACE/Global.hxx"
#include "Simulation/SimMACE/RunManager.hxx"

#include "G4VModularPhysicsList.hh"

namespace MACE::Simulation::SimMACE::Physics {

class PhysicsList final : public G4VModularPhysicsList {
    friend RunManager;

private:
    PhysicsList();
    ~PhysicsList() noexcept = default;

public:
    PhysicsList(const PhysicsList&) = delete;
    PhysicsList& operator=(const PhysicsList&) = delete;
};

} // namespace MACE::Simulation::SimMACE::Physics
