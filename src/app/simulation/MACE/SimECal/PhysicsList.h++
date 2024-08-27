#pragma once

#include "MACE/SimECal/Messenger/PhysicsMessenger.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

namespace MACE::SimECal {

class PhysicsList final : public Mustard::Env::Memory::PassiveSingleton<PhysicsList>,
                          public StandardPhysicsListBase {
public:
    PhysicsList();

    auto UseOpticalPhysics() -> void;

private:
    PhysicsMessenger::Register<PhysicsList> fMessengerRegister;
};

} // namespace MACE::SimECal
