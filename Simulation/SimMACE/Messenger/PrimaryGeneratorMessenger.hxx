#pragma once

#include "SimMACE/Global.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::SimMACE::Messenger {

class PrimaryGeneratorMessenger final : public G4UImessenger {
public:
    static PrimaryGeneratorMessenger& Instance();

private:
    PrimaryGeneratorMessenger();
    ~PrimaryGeneratorMessenger() noexcept = default;
    PrimaryGeneratorMessenger(const PrimaryGeneratorMessenger&) = delete;
    PrimaryGeneratorMessenger& operator=(const PrimaryGeneratorMessenger&) = delete;

public:
    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetFlux;
    G4UIcmdWithADoubleAndUnit fSetRepetitionRate;
    G4UIcmdWithADoubleAndUnit fSetTimeWidthRMS;
    G4UIcmdWithADoubleAndUnit fSetEnergy;
    G4UIcmdWithADoubleAndUnit fSetEnergySpreadRMS;
    G4UIcmdWithADoubleAndUnit fSetBeamProfileRMS;
    G4UIcmdWithAnInteger fSetMuonsForEachG4Event;
};

} // namespace MACE::Simulation::SimMACE::Messenger
