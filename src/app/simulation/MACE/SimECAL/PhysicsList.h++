#pragma once

#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

namespace MACE::SimECAL {

class PhysicsList final : public Mustard::Env::Memory::PassiveSingleton<PhysicsList>,
                          public StandardPhysicsListBase {
public:
    PhysicsList();

    void ConstructProcess() override;
};

} // namespace MACE::SimECAL
