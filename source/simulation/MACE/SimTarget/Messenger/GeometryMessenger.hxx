#pragma once

#include "MACE/Environment/Memory/Singleton.hxx"
#include "MACE/Utility/ObserverPtr.hxx"

#include "G4UImessenger.hh"

#include <memory>

class G4UIcmdWith3VectorAndUnit;
class G4UIcmdWithABool;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UICommand;
class G4UIdirectory;

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

    void SetNewValue(ObserverPtr<G4UIcommand> command, G4String value) override;

private:
    ObserverPtr<Action::DetectorConstruction> fDetectorConstruction;

    // std::unique_ptr<G4UIcmdWith3VectorAndUnit> fSetWorldHalfExtent;
    // std::unique_ptr<G4UIcmdWithABool> fSetEnableBeamMonitor;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetBeamMonitorWidth;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetBeamMonitorThickness;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetDistanceBetweenBeamMonitorAndTarget;
    // std::unique_ptr<G4UIcmdWithABool> fSetEnableDegrader;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetDegraderWidth;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetDegraderThickness;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetDistanceBetweenDegraderAndTarget;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetTargetWidth;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetTargetThickness;
    std::unique_ptr<G4UIcmdWithAString> fImportDescription;
    std::unique_ptr<G4UIcmdWithAString> fExportDescription;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetTargetDensity;
    std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetTemperature;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetAblationExtent;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetHoleSpacing;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetHoleDiameter;
    // std::unique_ptr<G4UIcmdWithADoubleAndUnit> fSetHoleDepth;
};

} // namespace Messenger

} // namespace MACE::SimTarget
