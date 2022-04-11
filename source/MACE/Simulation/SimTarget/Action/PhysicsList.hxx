#pragma once

#include "G4VModularPhysicsList.hh"

namespace MACE::Simulation::SimTarget::Action {

class PhysicsList final : public G4VModularPhysicsList {
public:
    PhysicsList();
    ~PhysicsList() noexcept = default;

    PhysicsList(const PhysicsList&) = delete;
    PhysicsList& operator=(const PhysicsList&) = delete;
};

} // namespace MACE::Simulation::SimTarget
