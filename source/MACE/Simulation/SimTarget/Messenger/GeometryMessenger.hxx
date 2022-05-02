#pragma once

#include "MACE/Simulation/SimTarget/Action/DetectorConstruction.hxx"

#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UImessenger.hh"

namespace MACE::Simulation::SimTarget::Messenger {

using Action::DetectorConstruction;
using Utility::ObserverPtr;

class GeometryMessenger final : public G4UImessenger {
public:
    static GeometryMessenger& Instance();

private:
    GeometryMessenger();
    ~GeometryMessenger() noexcept = default;
    GeometryMessenger(const GeometryMessenger&) = delete;
    GeometryMessenger& operator=(const GeometryMessenger&) = delete;

public:
    void SetTo(ObserverPtr<DetectorConstruction> dc) { fDetectorConstruction = dc; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<DetectorConstruction> fDetectorConstruction = nullptr;

    G4UIdirectory fDirectory;
    G4UIcmdWith3VectorAndUnit fSetWorldHalfExtent;
    G4UIcmdWithADoubleAndUnit fSetBeamCounterWidth;
    G4UIcmdWithADoubleAndUnit fSetBeamCounterThickness;
    G4UIcmdWithADoubleAndUnit fSetDistanceBetweenBeamCounterAndTarget;
    G4UIcmdWithADoubleAndUnit fSetDegraderWidth;
    G4UIcmdWithADoubleAndUnit fSetDegraderThickness;
    G4UIcmdWithADoubleAndUnit fSetDistanceBetweenDegraderAndTarget;
    G4UIcmdWithADoubleAndUnit fSetTargetWidth;
    G4UIcmdWithADoubleAndUnit fSetTargetThickness;
    G4UIcmdWithADoubleAndUnit fSetTargetDensity;
    G4UIcmdWithADoubleAndUnit fSetTemperature;
    G4UIcmdWithAString fSetFineStructure;
};

} // namespace MACE::Simulation::SimTarget::Messenger
