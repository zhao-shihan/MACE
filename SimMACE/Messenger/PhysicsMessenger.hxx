#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADouble.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Messenger::PhysicsMessenger final :
    public G4UImessenger {
public:
    static PhysicsMessenger& Instance();

private:
    PhysicsMessenger();
    ~PhysicsMessenger() noexcept;
    PhysicsMessenger(const PhysicsMessenger&) = delete;
    PhysicsMessenger& operator=(const PhysicsMessenger&) = delete;

public:
    void Set(Physics::MuoniumProduction* pMuoniumProduction) { fpMuoniumProduction = pMuoniumProduction; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Physics::MuoniumProduction* fpMuoniumProduction;

    G4UIdirectory* fDirectory;
    G4UIcmdWithADouble* fSetConversionProbability;
};
