#pragma once

#include "MACE/Env/Memory/Singleton.h++"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithABool;
class G4UIdirectory;

namespace MACE::SimTarget {

inline namespace Action {

class SteppingAction;

} // namespace Action

inline namespace Messenger {

class ActionMessenger final : public Env::Memory::Singleton<ActionMessenger>,
                              public G4UImessenger {
    friend Env::Memory::SingletonInstantiator;

private:
    ActionMessenger();
    ~ActionMessenger();

public:
    auto Register(gsl::not_null<SteppingAction*> sa) -> void { fSteppingAction = sa; }

    auto SetNewValue(G4UIcommand* command, G4String value) -> void override;

private:
    SteppingAction* fSteppingAction;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithABool> fKillIrrelevants;
};

} // namespace Messenger

} // namespace MACE::SimTarget
