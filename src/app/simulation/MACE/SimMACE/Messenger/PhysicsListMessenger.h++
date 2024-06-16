#pragma once

#include "Mustard/Extension/Geant4X/Interface/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithABool;

namespace MACE::SimMACE {

class PhysicsList;

inline namespace Messenger {

class PhysicsListMessenger final : public Mustard::Geant4X::SingletonMessenger<PhysicsListMessenger,
                                                                      PhysicsList> {
    friend class Mustard::Env::Memory::SingletonInstantiator;

private:
    PhysicsListMessenger();
    ~PhysicsListMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIcmdWithABool> fApplyMACEPxyCut;
};

} // namespace Messenger

} // namespace MACE::SimMACE
