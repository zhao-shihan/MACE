#pragma once

#include "Mustard/Extension/Geant4X/Interface/SingletonMessenger.h++"

#include "G4UIcmdWithABool.hh"

#include <memory>

namespace MACE::PhaseI::inline Simulation::inline Messenger {

template<typename AReceiver>
class NeutrinoKillerMessenger final : public Mustard::Geant4X::SingletonMessenger<NeutrinoKillerMessenger<AReceiver>,
                                                                                  AReceiver> {
    friend Mustard::Env::Memory::SingletonInstantiator;

private:
    NeutrinoKillerMessenger();
    ~NeutrinoKillerMessenger() = default;

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIcmdWithABool> fEnableNeutrinoKiller;
};

} // namespace MACE::PhaseI::inline Simulation::inline Messenger

#include "MACE/PhaseI/Simulation/Action/NeutrinoKillerMessenger.inl"
