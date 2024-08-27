#pragma once

#include "MACE/SimMACE/Messenger/PhysicsMessenger.h++"
#include "MACE/Simulation/Physics/StandardPhysicsList.h++"

#include "Mustard/Env/Memory/PassiveSingleton.h++"

#include "G4ParticleDefinition.hh"
#include "G4VDecayChannel.hh"

#include <concepts>

namespace MACE::SimMACE {

class PhysicsList final : public Mustard::Env::Memory::PassiveSingleton<PhysicsList>,
                          public StandardPhysicsListBase {
public:
    PhysicsList();

    auto MACEPxyCutMaxLowerPositronEk() const -> auto { return fMACEPxyCutMaxLowerPositronEk; }
    auto MACEPxyCutMaxLowerPositronEk(double val) -> void { fMACEPxyCutMaxLowerPositronEk = val; }

    auto ApplyMACEPxyCut(bool apply) -> void;

private:
    template<std::derived_from<G4VDecayChannel> C, std::derived_from<G4ParticleDefinition> P>
    auto FindICDecayChannel(const P* particle) -> C&;

private:
    double fMACEPxyCutMaxLowerPositronEk; // for mu+ and M IC decay

    PhysicsMessenger::Register<PhysicsList> fMessengerRegister;
};

} // namespace MACE::SimMACE
