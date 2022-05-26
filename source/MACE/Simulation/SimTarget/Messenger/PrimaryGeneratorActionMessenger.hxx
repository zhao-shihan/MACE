#pragma once

#include "MACE/Simulation/SimTarget/Action/PrimaryGeneratorAction.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::SimTarget::Messenger {

using Utility::ObserverPtr;

class PrimaryGeneratorActionMessenger final : public G4UImessenger {
public:
    static PrimaryGeneratorActionMessenger& Instance();

private:
    PrimaryGeneratorActionMessenger();
    ~PrimaryGeneratorActionMessenger() noexcept = default;
    PrimaryGeneratorActionMessenger(const PrimaryGeneratorActionMessenger&) = delete;
    PrimaryGeneratorActionMessenger& operator=(const PrimaryGeneratorActionMessenger&) = delete;

public:
    void SetTo(ObserverPtr<Action::PrimaryGeneratorAction> pga) { fPrimaryGeneratorAction = pga; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Action::PrimaryGeneratorAction> fPrimaryGeneratorAction;

    G4UIcmdWithAnInteger fSetMuonsForEachG4Event;
};

} // namespace MACE::Simulation::SimTarget::Messenger
