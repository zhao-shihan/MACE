#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4VModularPhysicsList.hh"

namespace MACE::SimMACE {

class PhysicsList final : public Env::Memory::PassiveSingleton<PhysicsList>,
                          public G4VModularPhysicsList {
public:
    PhysicsList();
};

} // namespace MACE::SimMACE
