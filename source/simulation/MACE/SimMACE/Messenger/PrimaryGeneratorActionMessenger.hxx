#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

#include "gsl/gsl"

namespace MACE::SimMACE {

namespace Action {

class PrimaryGeneratorAction;

} // namespace Action

namespace Messenger {

class PrimaryGeneratorActionMessenger final : public Env::Memory::Singleton<PrimaryGeneratorActionMessenger>,
                                              public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    PrimaryGeneratorActionMessenger();
    ~PrimaryGeneratorActionMessenger() = default;

public:
    void AssignTo(gsl::not_null<Action::PrimaryGeneratorAction*> pga) { fPrimaryGeneratorAction = pga; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Action::PrimaryGeneratorAction* fPrimaryGeneratorAction;

    G4UIcmdWithADoubleAndUnit fSetFlux;
    G4UIcmdWithADoubleAndUnit fSetRepetitionRate;
    G4UIcmdWithADoubleAndUnit fSetTimeWidthRMS;
    G4UIcmdWithAnInteger fSetMuonsForEachG4Event;
};

} // namespace Messenger

} // namespace MACE::SimMACE
