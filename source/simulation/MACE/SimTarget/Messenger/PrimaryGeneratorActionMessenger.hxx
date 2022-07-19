#pragma once

#include "MACE/Environment/Resource/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::SimTarget {

namespace Action {

class PrimaryGeneratorAction;

} // namespace Action

namespace Messenger {

using Utility::ObserverPtr;

class PrimaryGeneratorActionMessenger final : public Environment::Resource::Singleton<PrimaryGeneratorActionMessenger>,
                                              public G4UImessenger {
    friend Environment::Resource::SingletonFactory;

private:
    PrimaryGeneratorActionMessenger();
    ~PrimaryGeneratorActionMessenger() = default;
    PrimaryGeneratorActionMessenger(const PrimaryGeneratorActionMessenger&) = delete;
    PrimaryGeneratorActionMessenger& operator=(const PrimaryGeneratorActionMessenger&) = delete;

public:
    void SetTo(ObserverPtr<Action::PrimaryGeneratorAction> pga) { fPrimaryGeneratorAction = pga; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Action::PrimaryGeneratorAction> fPrimaryGeneratorAction;

    G4UIcmdWithAnInteger fSetMuonsForEachG4Event;
};

} // namespace Messenger

} // namespace MACE::SimTarget
