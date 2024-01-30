#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"

#include "G4VModularPhysicsList.hh"

class G4VModularPhysicsList;

namespace MACE::SimEMC {

class PhysicsList final : public Env::Memory::PassiveSingleton<PhysicsList>,
                          public G4VModularPhysicsList {
public:
    PhysicsList();

    auto UseOpticalPhysics() -> void;
};

} // namespace MACE::SimEMC
