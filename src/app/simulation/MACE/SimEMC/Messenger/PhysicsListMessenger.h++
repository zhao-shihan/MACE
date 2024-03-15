#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcommand;

namespace MACE::SimEMC {

class PhysicsList;

inline namespace Messenger {

class PhysicsListMessenger final : public Geant4X::SingletonMessenger<PhysicsListMessenger,
                                                                      PhysicsList> {
    friend Env::Memory::SingletonInstantiator;

private:
    PhysicsListMessenger();
    ~PhysicsListMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIcommand> fUseOpticalPhysics;
};

} // namespace Messenger

} // namespace MACE::SimEMC
