#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

#include "SimMACE/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::Messenger::MuonBeamMessenger final :
    public G4UImessenger {
public:
    static MuonBeamMessenger& Instance();

private:
    MuonBeamMessenger();
    ~MuonBeamMessenger() noexcept = default;
    MuonBeamMessenger(const MuonBeamMessenger&) = delete;
    MuonBeamMessenger& operator=(const MuonBeamMessenger&) = delete;

public:
    void Set(ObserverPtr<Action::PrimaryGeneratorAction> primaryGeneratorAction) { fPrimaryGeneratorAction = primaryGeneratorAction; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Action::PrimaryGeneratorAction> fPrimaryGeneratorAction = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetFlux;
    G4UIcmdWithADoubleAndUnit fSetPlusePeakInterval;
    G4UIcmdWithADoubleAndUnit fSetPluseWidthRMS;
    G4UIcmdWithADoubleAndUnit fSetEnergy;
    G4UIcmdWithADoubleAndUnit fSetEnergySpreadRMS;
    G4UIcmdWithADoubleAndUnit fSetBeamWidthRMS;
};
