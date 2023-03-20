#pragma once

#include "MACE/Env/Memory/PassiveSingleton.hxx"

#include "G4VModularPhysicsList.hh"

namespace MACE::SimTarget::inline Action {

class PhysicsList final : public Env::Memory::PassiveSingleton<PhysicsList>,
                          public G4VModularPhysicsList {
public:
    PhysicsList();
};

} // namespace MACE::SimTarget::inline Action
