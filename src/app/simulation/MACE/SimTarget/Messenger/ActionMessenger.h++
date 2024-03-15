#pragma once

#include "MACE/Extension/Geant4X/SingletonMessenger.h++"

#include <memory>

class G4UIcmdWithABool;
class G4UIdirectory;

namespace MACE::SimTarget {

inline namespace Action {

class SteppingAction;

} // namespace Action

inline namespace Messenger {

class ActionMessenger final : public Geant4X::SingletonMessenger<ActionMessenger,
                                                                 SteppingAction> {
    friend Env::Memory::SingletonInstantiator;

private:
    ActionMessenger();
    ~ActionMessenger();

public:
    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithABool> fKillIrrelevants;
};

} // namespace Messenger

} // namespace MACE::SimTarget
