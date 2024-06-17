#pragma once

#include "MACE/PhaseI/SimMACEPhaseI/Messenger/PhysicsListMessenger.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

namespace MACE::PhaseI::SimMACEPhaseI {

class PhysicsList final : public Mustard::Env::Memory::PassiveSingleton<PhysicsList>,
                          public StandardPhysicsListBase {
public:
    PhysicsList();

    auto UseOpticalPhysics() -> void;

private:
    PhysicsListMessenger::Register<PhysicsList> fMessengerRegister;
};

} // namespace MACE::PhaseI::SimMACEPhaseI
