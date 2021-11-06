#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "SimG4/Global.hh"

class MACE::SimG4::Messenger::MuonBeamMessenger final :
    public G4UImessenger {
public:
    static MuonBeamMessenger* Instance();
private:
    MuonBeamMessenger();
    ~MuonBeamMessenger();
    MuonBeamMessenger(const MuonBeamMessenger&) = delete;
    MuonBeamMessenger& operator=(const MuonBeamMessenger&) = delete;

public:
    void Set(Action::PrimaryGeneratorAction* pPrimaryGeneratorAction) { fpPrimaryGeneratorAction = pPrimaryGeneratorAction; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    Action::PrimaryGeneratorAction* fpPrimaryGeneratorAction;

    G4UIdirectory* fDirectory;
    G4UIcmdWithADoubleAndUnit* fSetFlux;
    G4UIcmdWithADoubleAndUnit* fSetPlusePeakInterval;
    G4UIcmdWithADoubleAndUnit* fSetPluseWidthRMS;
    G4UIcmdWithADoubleAndUnit* fSetEnergy;
    G4UIcmdWithADoubleAndUnit* fSetEnergySpreadRMS;
    G4UIcmdWithADoubleAndUnit* fSetBeamWidthRMS;
};
