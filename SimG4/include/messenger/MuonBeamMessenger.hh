#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "SimG4Global.hh"

class MACE::SimG4::MuonBeamMessenger : public G4UImessenger {
public:
    static MuonBeamMessenger* Instance();
private:
    MuonBeamMessenger();
    ~MuonBeamMessenger();
    MuonBeamMessenger(const MuonBeamMessenger&) = delete;
    MuonBeamMessenger& operator=(const MuonBeamMessenger&) = delete;
    
public:
    void SetPrimaryGeneratorAction(PrimaryGeneratorAction* pPrimaryGeneratorAction) { fpPrimaryGeneratorAction = pPrimaryGeneratorAction; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    PrimaryGeneratorAction* fpPrimaryGeneratorAction;
    
    G4UIdirectory* fDirectory;
    G4UIcmdWithADoubleAndUnit* fSetFlux;
    G4UIcmdWithADoubleAndUnit* fSetPlusePeakInterval;
    G4UIcmdWithADoubleAndUnit* fSetPluseWidthRMS;
    G4UIcmdWithADoubleAndUnit* fSetEnergy;
    G4UIcmdWithADoubleAndUnit* fSetEnergySpreadRMS;
    G4UIcmdWithADoubleAndUnit* fSetBeamWidthRMS;
};
