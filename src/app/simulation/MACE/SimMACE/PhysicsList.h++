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

    auto MACEBiasPxySofteningFactor() const -> auto { return fMACEBiasPxySofteningFactor; }
    auto MACEBiasCosSofteningFactor() const -> auto { return fMACEBiasCosSofteningFactor; }
    auto MACEBiasEkLow() const -> auto { return fMACEBiasEkLow; }
    auto MACEBiasEkSofteningFactor() const -> auto { return fMACEBiasEkSofteningFactor; }

    auto MACEBiasPxySofteningFactor(double val) { fMACEBiasPxySofteningFactor = val; }
    auto MACEBiasCosSofteningFactor(double val) { fMACEBiasCosSofteningFactor = val; }
    auto MACEBiasEkLow(double val) { fMACEBiasEkLow = val; }
    auto MACEBiasEkSofteningFactor(double val) { fMACEBiasEkSofteningFactor = val; }

    auto ApplyMACEBias(bool apply) -> void;

private:
    template<std::derived_from<G4VDecayChannel> C, std::derived_from<G4ParticleDefinition> P>
    auto FindICDecayChannel(const P* particle) -> C&;

private:
    double fMACEBiasPxySofteningFactor;
    double fMACEBiasCosSofteningFactor;
    double fMACEBiasEkLow;
    double fMACEBiasEkSofteningFactor;

    PhysicsMessenger::Register<PhysicsList> fMessengerRegister;
};

} // namespace MACE::SimMACE
