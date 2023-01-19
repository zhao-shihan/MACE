#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UImessenger.hh"

#include "gsl/gsl"

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
    ~ActionMessenger() = default;

public:
    void AssignTo(gsl::not_null<Action::SteppingAction*> sa) { fSteppingAction = sa; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Action::SteppingAction* fSteppingAction;

    G4UIdirectory fDirectory;
    G4UIcmdWithABool fSetKillIrrelevants;
};

} // namespace Messenger

} // namespace MACE::SimTarget
