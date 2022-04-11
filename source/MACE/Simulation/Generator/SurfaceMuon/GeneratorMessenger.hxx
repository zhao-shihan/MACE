#pragma once

#include "MACE/Simulation/Generator/SurfaceMuon/PrimaryGeneratorAction.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::Generator::SurfaceMuon {

using Utility::ObserverPtr;

class GeneratorMessenger final : public G4UImessenger {
public:
    static GeneratorMessenger& Instance();

private:
    GeneratorMessenger();
    ~GeneratorMessenger() noexcept = default;
    GeneratorMessenger(const GeneratorMessenger&) = delete;
    GeneratorMessenger& operator=(const GeneratorMessenger&) = delete;

public:
    void SetTo(ObserverPtr<PrimaryGeneratorAction> pga) { fPrimaryGeneratorAction = pga; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<PrimaryGeneratorAction> fPrimaryGeneratorAction;

    G4UIdirectory fDirectory;
    G4UIcmdWithADoubleAndUnit fSetFlux;
    G4UIcmdWithADoubleAndUnit fSetRepetitionRate;
    G4UIcmdWithADoubleAndUnit fSetTimeWidthRMS;
    G4UIcmdWithADoubleAndUnit fSetEnergy;
    G4UIcmdWithADoubleAndUnit fSetEnergySpreadRMS;
    G4UIcmdWithADoubleAndUnit fSetBeamProfileRMS;
    G4UIcmdWithAnInteger fSetMuonsForEachG4Event;
};

} // namespace MACE::Simulation::Generator::SurfaceMuon
