#pragma once

#include "MACE/Env/Memory/FreeSingleton.hxx"

#include "G4VModularPhysicsList.hh"

namespace MACE::SimGuide::inline Action {

class PhysicsList final : public Env::Memory::FreeSingleton<PhysicsList>,
                          public G4VModularPhysicsList {
public:
    PhysicsList();
};

} // namespace MACE::SimGuide::inline Action
