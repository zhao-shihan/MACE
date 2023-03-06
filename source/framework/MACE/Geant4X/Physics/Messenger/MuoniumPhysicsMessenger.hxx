#pragma once

#include "MACE/Env/Memory/Singleton.hxx"

#include "G4UImessenger.hh"

#include "gsl/gsl"

#include <memory>

class G4UIcmdWithABool;
class G4UIcmdWithADouble;
class G4UIcmdWithADoubleAndUnit;
class G4UIdirectory;

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
    ~MuoniumPhysicsMessenger();

public:
    void AssignTo(gsl::not_null<Process::MuoniumFormation*> mf) { fMuoniumFormation = mf; }
    void AssignTo(gsl::not_null<Process::MuoniumTransport*> mt) { fMuoniumTransport = mt; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Process::MuoniumFormation* fMuoniumFormation;
    Process::MuoniumTransport* fMuoniumTransport;

    std::unique_ptr<G4UIdirectory> fMuoniumPhysicsDirectory;

    std::unique_ptr<G4UIdirectory> fFormationProcessDirectory;
    std::unique_ptr<G4UIcmdWithADouble> fSetFormationProbability;
    std::unique_ptr<G4UIcmdWithADouble> fSetConversionProbability;

    std::unique_ptr<G4UIdirectory> fTransportProcessDirectory;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetMeanFreePath;
    std::unique_ptr<G4UIcmdWithABool> fSetManipulateAllSteps;
};

} // namespace Messenger

} // namespace MACE::Geant4X::Physics
