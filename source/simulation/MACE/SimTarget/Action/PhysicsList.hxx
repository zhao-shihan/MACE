#pragma once

#include "MACE/Environment/Memory/FreeSingleton.hxx"

#include "G4VModularPhysicsList.hh"

namespace MACE::SimTarget::Action {

class PhysicsList final : public Environment::Memory::FreeSingleton<PhysicsList>,
                          public G4VModularPhysicsList {
public:
    PhysicsList();
};

} // namespace MACE::SimTarget::Action
