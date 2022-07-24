#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithABool.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIdirectory.hh"
#include "G4UImessenger.hh"

namespace MACE::SimTarget {

namespace Action {

class DetectorConstruction;

} // namespace Action

namespace Messenger {

using Utility::ObserverPtr;

class GeometryMessenger final : public Environment::Memory::Singleton<GeometryMessenger>,
                                public G4UImessenger {
    friend Environment::Memory::SingletonFactory;

private:
    GeometryMessenger();
    ~GeometryMessenger() = default;
    GeometryMessenger(const GeometryMessenger&) = delete;
    GeometryMessenger& operator=(const GeometryMessenger&) = delete;

public:
    void SetTo(ObserverPtr<Action::DetectorConstruction> dc) { fDetectorConstruction = dc; }

    void SetNewValue(G4UIcommand* command, G4String value) override;

private:
    ObserverPtr<Action::DetectorConstruction> fDetectorConstruction;

    G4UIdirectory fDirectory;
    G4UIcmdWith3VectorAndUnit fSetWorldHalfExtent;
    G4UIcmdWithABool fSetEnableBeamMonitor;
    G4UIcmdWithADoubleAndUnit fSetBeamMonitorWidth;
    G4UIcmdWithADoubleAndUnit fSetBeamMonitorThickness;
    G4UIcmdWithADoubleAndUnit fSetDistanceBetweenBeamMonitorAndTarget;
    G4UIcmdWithABool fSetEnableDegrader;
    G4UIcmdWithADoubleAndUnit fSetDegraderWidth;
    G4UIcmdWithADoubleAndUnit fSetDegraderThickness;
    G4UIcmdWithADoubleAndUnit fSetDistanceBetweenDegraderAndTarget;
    G4UIcmdWithADoubleAndUnit fSetTargetWidth;
    G4UIcmdWithADoubleAndUnit fSetTargetThickness;
    G4UIcmdWithADoubleAndUnit fSetTargetDensity;
    G4UIcmdWithADoubleAndUnit fSetTemperature;
    G4UIcmdWithAString fSetFineStructure;
};

} // namespace Messenger

} // namespace MACE::SimTarget
