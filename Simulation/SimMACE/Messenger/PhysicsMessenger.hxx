#pragma once

#include "Utility/ObserverPtr.hxx"
#include "Simulation/SimMACE/Global.hxx"
#include "Simulation/SimMACE/Physics/MuoniumProduction.hxx"

#include "G4UIcmdWithADouble.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::SimMACE::Messenger {

using Utility::ObserverPtr;
using namespace Physics;

class PhysicsMessenger final : public G4UImessenger {
public:
    static PhysicsMessenger& Instance();

private:
    PhysicsMessenger();
    ~PhysicsMessenger() noexcept = default;
    PhysicsMessenger(const PhysicsMessenger&) = delete;
    PhysicsMessenger& operator=(const PhysicsMessenger&) = delete;

public:
    void Set(ObserverPtr<MuoniumProduction> muoniumProduction) { fMuoniumProduction = muoniumProduction; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<MuoniumProduction> fMuoniumProduction = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWithADouble fSetConversionProbability;
};

} // namespace MACE::Simulation::SimMACE::Messenger
