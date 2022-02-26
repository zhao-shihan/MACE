#pragma once

#include "G4UImessenger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"

#include "SimMACE/Global.hxx"
#include "Utility/ObserverPtr.hxx"

class MACE::SimMACE::Messenger::PrimaryGeneratorMessenger final :
    public G4UImessenger {
public:
    static PrimaryGeneratorMessenger& Instance();

private:
    PrimaryGeneratorMessenger();
    ~PrimaryGeneratorMessenger() noexcept = default;
    PrimaryGeneratorMessenger(const PrimaryGeneratorMessenger&) = delete;
    PrimaryGeneratorMessenger& operator=(const PrimaryGeneratorMessenger&) = delete;

public:
    void Set(ObserverPtr<Action::PrimaryGeneratorAction> primaryGeneratorAction) { fPrimaryGeneratorAction = primaryGeneratorAction; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Action::PrimaryGeneratorAction> fPrimaryGeneratorAction = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetFlux;
    G4UIcmdWithADoubleAndUnit fSetRepetitionRate;
    G4UIcmdWithADoubleAndUnit fSetTimeWidthRMS;
    G4UIcmdWithADoubleAndUnit fSetEnergy;
    G4UIcmdWithADoubleAndUnit fSetEnergySpreadRMS;
    G4UIcmdWithADoubleAndUnit fSetBeamProfileRMS;
    G4UIcmdWithAnInteger fSetMuonsPerG4Event;
};
