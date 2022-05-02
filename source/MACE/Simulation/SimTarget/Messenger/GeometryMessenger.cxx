#include "MACE/Core/Geometry/Description/BeamCounter.hxx"
#include "MACE/Core/Geometry/Description/BeamDegrader.hxx"
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
    fSetBeamCounterWidth("/MACE/Geometry/SetBeamCounterWidth", this),
    fSetBeamCounterThickness("/MACE/Geometry/SetBeamCounterThickness", this),
    fSetDistanceBetweenBeamCounterAndTarget("/MACE/Geometry/SetDistanceBetweenBeamCounterAndTarget", this),
    fSetDegraderWidth("/MACE/Geometry/SetDegraderWidth", this),
    fSetDegraderThickness("/MACE/Geometry/SetDegraderThickness", this),
    fSetDistanceBetweenDegraderAndTarget("/MACE/Geometry/SetDistanceBetweenDegraderAndTarget", this),
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

    fSetBeamCounterWidth.SetGuidance("Set beam counter width.");
    fSetBeamCounterWidth.SetParameterName("w", false);
    fSetBeamCounterWidth.SetUnitCategory("Length");
    fSetBeamCounterWidth.AvailableForStates(G4State_PreInit);

    fSetBeamCounterThickness.SetGuidance("Set beam counter thickness.");
    fSetBeamCounterThickness.SetParameterName("t", false);
    fSetBeamCounterThickness.SetUnitCategory("Length");
    fSetBeamCounterThickness.AvailableForStates(G4State_PreInit);

    fSetDistanceBetweenDegraderAndTarget.SetGuidance("Set distance between degrader downstream surface and target upstream surface.");
    fSetDistanceBetweenDegraderAndTarget.SetParameterName("d", false);
    fSetDistanceBetweenDegraderAndTarget.SetUnitCategory("Length");
    fSetDistanceBetweenDegraderAndTarget.AvailableForStates(G4State_PreInit);

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
    } else if (command == std::addressof(fSetDegraderWidth)) {
        Description::BeamDegrader::Instance().SetWidth(fSetDegraderWidth.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetDegraderThickness)) {
        Description::BeamDegrader::Instance().SetThickness(fSetDegraderThickness.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetDistanceBetweenDegraderAndTarget)) {
        Description::BeamDegrader::Instance().SetDistanceToTargetSurface(fSetDistanceBetweenDegraderAndTarget.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetBeamCounterWidth)) {
        Description::BeamCounter::Instance().SetWidth(fSetBeamCounterWidth.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetBeamCounterThickness)) {
        Description::BeamCounter::Instance().SetThickness(fSetBeamCounterThickness.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetDistanceBetweenBeamCounterAndTarget)) {
        Description::BeamCounter::Instance().SetDistanceToTargetSurface(fSetDistanceBetweenBeamCounterAndTarget.GetNewDoubleValue(value));
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
