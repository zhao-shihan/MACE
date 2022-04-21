#pragma once

#include "MACE/Simulation/SimTarget/Action/SteppingAction.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::SimTarget::Messenger {

using Action::SteppingAction;
using Utility::ObserverPtr;

class ActionMessenger final : public G4UImessenger {
public:
    static ActionMessenger& Instance();

private:
    ActionMessenger();
    ~ActionMessenger() noexcept = default;
    ActionMessenger(const ActionMessenger&) = delete;
    ActionMessenger& operator=(const ActionMessenger&) = delete;

public:
    void SetTo(ObserverPtr<SteppingAction> sa) { fSteppingAction = sa; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<SteppingAction> fSteppingAction = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWithABool fSetKillDecayProducts;
};

} // namespace MACE::Simulation::SimTarget::Messenger
