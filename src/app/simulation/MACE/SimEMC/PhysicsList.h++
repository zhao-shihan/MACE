#pragma once

#include "MACE/SimEMC/Messenger/PhysicsListMessenger.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

namespace MACE::SimEMC {

class PhysicsList final : public Mustard::Env::Memory::PassiveSingleton<PhysicsList>,
                          public StandardPhysicsListBase {
public:
    PhysicsList();

    auto UseOpticalPhysics() -> void;

private:
    PhysicsListMessenger::Register<PhysicsList> fMessengerRegister;
};

} // namespace MACE::SimEMC
