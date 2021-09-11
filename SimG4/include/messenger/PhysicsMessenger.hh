#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADouble.hh"

#include "SimG4Global.hh"

class MACE::SimG4::PhysicsMessenger final : public G4UImessenger {
public:
    static PhysicsMessenger* Instance();
private:
    PhysicsMessenger();
    ~PhysicsMessenger();
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
