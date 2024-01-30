#pragma once

#include "MACE/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimEMC/Messenger/PhysicsListMessenger.h++"

#include "FTFP_BERT.hh"

namespace MACE::SimEMC {

class PhysicsList final : public Env::Memory::PassiveSingleton<PhysicsList>,
                          public FTFP_BERT {
public:
    PhysicsList();

    auto UseOpticalPhysics() -> void;

private:
    PhysicsListMessenger::Register<PhysicsList> fMessengerRegister;
};

} // namespace MACE::SimEMC
