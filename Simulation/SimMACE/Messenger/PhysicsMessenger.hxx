#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADouble.hh"

#include "SimMACE/Global.hxx"
#include "ObserverPtr.hxx"

class MACE::SimMACE::PhysicsMessenger final :
    public G4UImessenger {
public:
    static PhysicsMessenger& Instance();

private:
    PhysicsMessenger();
    ~PhysicsMessenger() noexcept = default;
    PhysicsMessenger(const PhysicsMessenger&) = delete;
    PhysicsMessenger& operator=(const PhysicsMessenger&) = delete;

public:
    void Set(ObserverPtr<Physics::MuoniumProduction> muoniumProduction) { fMuoniumProduction = muoniumProduction; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Physics::MuoniumProduction> fMuoniumProduction = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWithADouble fSetConversionProbability;
};
