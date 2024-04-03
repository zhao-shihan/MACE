#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimEMC/Messenger/PhysicsListMessenger.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

namespace MACE::SimEMC {

class PhysicsList final : public Env::Memory::PassiveSingleton<PhysicsList>,
                          public StandardPhysicsListBase {
public:
    PhysicsList();

    auto UseOpticalPhysics() -> void;

private:
    PhysicsListMessenger::Register<PhysicsList> fMessengerRegister;
};

} // namespace MACE::SimEMC
