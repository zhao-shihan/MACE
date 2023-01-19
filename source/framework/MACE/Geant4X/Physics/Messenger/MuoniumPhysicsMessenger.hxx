#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

#include "gsl/gsl"

namespace MACE::Geant4X::Physics {

namespace Process {

class MuoniumFormation;
class MuoniumTransport;

} // namespace Process

namespace Messenger {

class MuoniumPhysicsMessenger final : public Env::Memory::Singleton<MuoniumPhysicsMessenger>,
                                      public G4UImessenger {
    friend Env::Memory::SingletonFactory;

private:
    MuoniumPhysicsMessenger();
    ~MuoniumPhysicsMessenger() = default;

public:
    void AssignTo(gsl::not_null<Process::MuoniumFormation*> mf) { fMuoniumFormation = mf; }
    void AssignTo(gsl::not_null<Process::MuoniumTransport*> mt) { fMuoniumTransport = mt; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Process::MuoniumFormation* fMuoniumFormation;
    Process::MuoniumTransport* fMuoniumTransport;

    G4UIdirectory fMuoniumPhysicsDirectory;

    G4UIdirectory fFormationProcessDirectory;
    G4UIcmdWithADouble fSetFormationProbability;
    G4UIcmdWithADouble fSetConversionProbability;

    G4UIdirectory fTransportProcessDirectory;
    G4UIcmdWithADoubleAndUnit fSetMeanFreePath;
    G4UIcmdWithABool fSetManipulateAllSteps;
};

} // namespace Messenger

} // namespace MACE::Geant4X::Physics
