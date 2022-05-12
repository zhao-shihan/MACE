#include "MACE/Core/Geometry/Description/BeamDegrader.hxx"
#include "MACE/Core/Geometry/Description/BeamMonitor.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Core/Geometry/Description/World.hxx"
#include "MACE/Simulation/SimTarget/Messenger/GeometryMessenger.hxx"
#include "MACE/Simulation/SimTarget/RunManager.hxx"

#include "G4UIdirectory.hh"

namespace MACE::Simulation::SimTarget::Messenger {

GeometryMessenger& GeometryMessenger::Instance() {
    static GeometryMessenger instance;
    return instance;
}

GeometryMessenger::GeometryMessenger() :
    G4UImessenger(),
    fDirectory("/MACE/Geometry/"),
    fSetWorldHalfExtent("/MACE/Geometry/SetWorldHalfExtent", this),
    fSetEnableDegrader("/MACE/Geometry/SetEnableDegrader", this),
    fSetDegraderWidth("/MACE/Geometry/SetDegraderWidth", this),
    fSetDegraderThickness("/MACE/Geometry/SetDegraderThickness", this),
    fSetDistanceBetweenDegraderAndTarget("/MACE/Geometry/SetDistanceBetweenDegraderAndTarget", this),
    fSetEnableBeamMonitor("/MACE/Geometry/SetEnableBeamMonitor", this),
    fSetBeamMonitorWidth("/MACE/Geometry/SetBeamMonitorWidth", this),
    fSetBeamMonitorThickness("/MACE/Geometry/SetBeamMonitorThickness", this),
    fSetDistanceBetweenBeamMonitorAndTarget("/MACE/Geometry/SetDistanceBetweenBeamMonitorAndTarget", this),
    fSetTargetWidth("/MACE/Geometry/SetTargetWidth", this),
    fSetTargetThickness("/MACE/Geometry/SetTargetThickness", this),
    fSetTargetDensity("/MACE/Geometry/SetTargetDensity", this),
    fSetTemperature("/MACE/Geometry/SetTemperature", this),
    fSetFineStructure("/MACE/Geometry/SetFineStructure", this) {

    fDirectory.SetGuidance("SimTarget geometry controller.");

    fSetWorldHalfExtent.SetGuidance("Set half extents of the world.");
    fSetWorldHalfExtent.SetParameterName("x", "y", "z", false);
    fSetWorldHalfExtent.SetUnitCategory("Length");
    fSetWorldHalfExtent.AvailableForStates(G4State_PreInit);

    fSetEnableDegrader.SetGuidance("Set true to enable placement of beam degrader, and vice versa.");
    fSetEnableDegrader.SetParameterName("b", false);
    fSetEnableDegrader.AvailableForStates(G4State_PreInit);

    fSetDegraderWidth.SetGuidance("Set beam degrader width.");
    fSetDegraderWidth.SetParameterName("w", false);
    fSetDegraderWidth.SetUnitCategory("Length");
    fSetDegraderWidth.AvailableForStates(G4State_PreInit);

    fSetDegraderThickness.SetGuidance("Set beam degrader thickness.");
    fSetDegraderThickness.SetParameterName("t", false);
    fSetDegraderThickness.SetUnitCategory("Length");
    fSetDegraderThickness.AvailableForStates(G4State_PreInit);

    fSetDistanceBetweenDegraderAndTarget.SetGuidance("Set distance between degrader downstream surface and target upstream surface.");
    fSetDistanceBetweenDegraderAndTarget.SetParameterName("d", false);
    fSetDistanceBetweenDegraderAndTarget.SetUnitCategory("Length");
    fSetDistanceBetweenDegraderAndTarget.AvailableForStates(G4State_PreInit);

    fSetEnableBeamMonitor.SetGuidance("Set true to enable placement of beam monitor, and vice versa.");
    fSetEnableBeamMonitor.SetParameterName("b", false);
    fSetEnableBeamMonitor.AvailableForStates(G4State_PreInit);

    fSetBeamMonitorWidth.SetGuidance("Set beam counter width.");
    fSetBeamMonitorWidth.SetParameterName("w", false);
    fSetBeamMonitorWidth.SetUnitCategory("Length");
    fSetBeamMonitorWidth.AvailableForStates(G4State_PreInit);

    fSetBeamMonitorThickness.SetGuidance("Set beam counter thickness.");
    fSetBeamMonitorThickness.SetParameterName("t", false);
    fSetBeamMonitorThickness.SetUnitCategory("Length");
    fSetBeamMonitorThickness.AvailableForStates(G4State_PreInit);

    fSetDistanceBetweenBeamMonitorAndTarget.SetGuidance("Set distance between beam monitor downstream surface and target upstream surface.");
    fSetDistanceBetweenBeamMonitorAndTarget.SetParameterName("d", false);
    fSetDistanceBetweenBeamMonitorAndTarget.SetUnitCategory("Length");
    fSetDistanceBetweenBeamMonitorAndTarget.AvailableForStates(G4State_PreInit);

    fSetTargetWidth.SetGuidance("Set target width.");
    fSetTargetWidth.SetParameterName("w", false);
    fSetTargetWidth.SetUnitCategory("Length");
    fSetTargetWidth.AvailableForStates(G4State_PreInit);

    fSetTargetThickness.SetGuidance("Set target thickness.");
    fSetTargetThickness.SetParameterName("t", false);
    fSetTargetThickness.SetUnitCategory("Length");
    fSetTargetThickness.AvailableForStates(G4State_PreInit);

    fSetTargetDensity.SetGuidance("Set target density.");
    fSetTargetDensity.SetParameterName("rho", false);
    fSetTargetDensity.SetUnitCategory("Volumic Mass");
    fSetTargetDensity.AvailableForStates(G4State_PreInit);

    fSetTemperature.SetGuidance("Set environment temperature.");
    fSetTemperature.SetParameterName("T", false);
    fSetTemperature.SetUnitCategory("Temperature");
    fSetTemperature.AvailableForStates(G4State_PreInit);

    fSetFineStructure.SetGuidance("Set boolean expression to represent the target fine structure. Where the expression evaluate to true is solid region.");
    fSetFineStructure.SetParameterName("expr", false);
    fSetFineStructure.AvailableForStates(G4State_Idle);
}

void GeometryMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    using namespace Core::Geometry;
    if (command == std::addressof(fSetWorldHalfExtent)) {
        auto& world = Description::World::Instance();
        auto halfExtent = fSetWorldHalfExtent.GetNew3VectorValue(value);
        world.SetHalfXExtent(halfExtent.x());
        world.SetHalfYExtent(halfExtent.y());
        world.SetHalfZExtent(halfExtent.z());
    } else if (command == std::addressof(fSetEnableBeamMonitor)) {
        Description::BeamMonitor::Instance().SetEnable(fSetEnableBeamMonitor.GetNewBoolValue(value));
    } else if (command == std::addressof(fSetBeamMonitorWidth)) {
        Description::BeamMonitor::Instance().SetWidth(fSetBeamMonitorWidth.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetBeamMonitorThickness)) {
        Description::BeamMonitor::Instance().SetThickness(fSetBeamMonitorThickness.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetDistanceBetweenBeamMonitorAndTarget)) {
        Description::BeamMonitor::Instance().SetDistanceToTargetSurface(fSetDistanceBetweenBeamMonitorAndTarget.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetEnableDegrader)) {
        Description::BeamDegrader::Instance().SetEnable(fSetEnableDegrader.GetNewBoolValue(value));
    } else if (command == std::addressof(fSetDegraderWidth)) {
        Description::BeamDegrader::Instance().SetWidth(fSetDegraderWidth.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetDegraderThickness)) {
        Description::BeamDegrader::Instance().SetThickness(fSetDegraderThickness.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetDistanceBetweenDegraderAndTarget)) {
        Description::BeamDegrader::Instance().SetDistanceToTargetSurface(fSetDistanceBetweenDegraderAndTarget.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetTargetWidth)) {
        Description::Target::Instance().SetWidth(fSetTargetWidth.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetTargetThickness)) {
        Description::Target::Instance().SetThickness(fSetTargetThickness.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetTargetDensity)) {
        fDetectorConstruction->SetTargetDensity(fSetTargetDensity.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetTemperature)) {
        fDetectorConstruction->SetTemperature(fSetTemperature.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetFineStructure)) {
        Description::Target::Instance().SetFineStructure(value);
    }
}

} // namespace MACE::Simulation::SimTarget::Messenger
