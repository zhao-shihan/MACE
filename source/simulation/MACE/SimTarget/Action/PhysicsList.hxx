#pragma once

#include "G4VModularPhysicsList.hh"

namespace MACE::SimTarget::Action {

class PhysicsList final : public G4VModularPhysicsList {
public:
    PhysicsList();
    ~PhysicsList() = default;
    PhysicsList(const PhysicsList&) = delete;
    PhysicsList& operator=(const PhysicsList&) = delete;
};

} // namespace MACE::SimTarget::Action
