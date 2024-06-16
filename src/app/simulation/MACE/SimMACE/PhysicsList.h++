#pragma once

#include "Mustard/Env/Memory/PassiveSingleton.h++"
#include "MACE/SimMACE/Messenger/PhysicsListMessenger.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "G4ParticleDefinition.hh"
#include "G4VDecayChannel.hh"

#include <concepts>

namespace MACE::SimMACE {

class PhysicsList final : public Mustard::Env::Memory::PassiveSingleton<PhysicsList>,
                          public StandardPhysicsListBase {
public:
    PhysicsList();

    auto ApplyMACEPxyCut(bool apply) -> void;

private:
    template<std::derived_from<G4VDecayChannel> C, std::derived_from<G4ParticleDefinition> P>
    auto FindIPPDecayChannel(const P* particle) -> C&;

private:
    PhysicsListMessenger::Register<PhysicsList> fMessengerRegister;
};

} // namespace MACE::SimMACE
