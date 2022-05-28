#pragma once

#include "MACE/Simulation/Physics/Process/MuoniumFormation.hxx"
#include "MACE/Simulation/Physics/Process/MuoniumTransport.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::Physics::Messenger {

using namespace Process;
using Utility::ObserverPtr;

class MuoniumPhysicsMessenger final : public G4UImessenger {
public:
    static MuoniumPhysicsMessenger& Instance();

private:
    MuoniumPhysicsMessenger();
    ~MuoniumPhysicsMessenger() noexcept = default;
    MuoniumPhysicsMessenger(const MuoniumPhysicsMessenger&) = delete;
    MuoniumPhysicsMessenger& operator=(const MuoniumPhysicsMessenger&) = delete;

public:
    void SetTo(ObserverPtr<MuoniumFormation> mf) { fMuoniumFormation = mf; }
    void SetTo(ObserverPtr<MuoniumTransport> mt) { fMuoniumTransport = mt; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<MuoniumFormation> fMuoniumFormation = nullptr;
    ObserverPtr<MuoniumTransport> fMuoniumTransport = nullptr;

    G4UIdirectory fMuoniumPhysicsDirectory;

    G4UIdirectory fFormationProcessDirectory;
    G4UIcmdWithADouble fSetFormationProbability;
    G4UIcmdWithADouble fSetConversionProbability;

    G4UIdirectory fTransportProcessDirectory;
    G4UIcmdWithADoubleAndUnit fSetMeanFreePath;
    G4UIcmdWithABool fSetManipulateAllSteps;
};

} // namespace MACE::Simulation::Physics::Messenger
