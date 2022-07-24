#pragma once

#include "MACE/Environment/Resource/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::SimulationG4::Physics {

namespace Process {

class MuoniumFormation;
class MuoniumTransport;

} // namespace Process

namespace Messenger {

using Utility::ObserverPtr;

class MuoniumPhysicsMessenger final : public Environment::Memory::Singleton<MuoniumPhysicsMessenger>,
                                      public G4UImessenger {
    friend Environment::Memory::SingletonFactory;

private:
    MuoniumPhysicsMessenger();
    ~MuoniumPhysicsMessenger() = default;

public:
    void SetTo(ObserverPtr<Process::MuoniumFormation> mf) { fMuoniumFormation = mf; }
    void SetTo(ObserverPtr<Process::MuoniumTransport> mt) { fMuoniumTransport = mt; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Process::MuoniumFormation> fMuoniumFormation;
    ObserverPtr<Process::MuoniumTransport> fMuoniumTransport;

    G4UIdirectory fMuoniumPhysicsDirectory;

    G4UIdirectory fFormationProcessDirectory;
    G4UIcmdWithADouble fSetFormationProbability;
    G4UIcmdWithADouble fSetConversionProbability;

    G4UIdirectory fTransportProcessDirectory;
    G4UIcmdWithADoubleAndUnit fSetMeanFreePath;
    G4UIcmdWithABool fSetManipulateAllSteps;
};

} // namespace Messenger

} // namespace MACE::SimulationG4::Physics
