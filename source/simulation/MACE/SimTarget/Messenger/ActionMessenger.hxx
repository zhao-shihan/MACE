#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithABool;
class G4UIdirectory;

namespace MACE::SimTarget {

namespace Action {

class SteppingAction;

} // namespace Action

namespace Messenger {

class ActionMessenger final : public Env::Memory::Singleton<ActionMessenger>,
                              public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    ActionMessenger();
    ~ActionMessenger();

public:
    void AssignTo(gsl::not_null<Action::SteppingAction*> sa) { fSteppingAction = sa; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Action::SteppingAction* fSteppingAction;

    std::unique_ptr<G4UIdirectory> fDirectory;
    std::unique_ptr<G4UIcmdWithABool> fKillIrrelevants;
};

} // namespace Messenger

} // namespace MACE::SimTarget
