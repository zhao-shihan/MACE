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
    fSetTargetWidth("/MACE/Geometry/SetTargetWidth", this),
    fSetTargetThickness("/MACE/Geometry/SetTargetThickness", this),
    fSetTargetDensity("/MACE/Geometry/SetTargetDensity", this),
    fSetTemperature("/MACE/Geometry/SetTemperature", this),
    fSetFineStructure("/MACE/Geometry/SetFineStructure", this) {

    fDirectory.SetGuidance("SimTarget geometry controller.");

    fSetWorldHalfExtent.SetParameterName("half x", "half y", "half z", false);
    fSetWorldHalfExtent.SetUnitCategory("Length");
    fSetWorldHalfExtent.AvailableForStates(G4State_PreInit);

    fSetTargetWidth.SetParameterName("Target width", false);
    fSetTargetWidth.SetUnitCategory("Length");
    fSetTargetWidth.AvailableForStates(G4State_PreInit);

    fSetTargetThickness.SetParameterName("Target thickness", false);
    fSetTargetThickness.SetUnitCategory("Length");
    fSetTargetThickness.AvailableForStates(G4State_PreInit);

    fSetTargetDensity.SetParameterName("density", false);
    fSetTargetDensity.SetUnitCategory("Volumic Mass");
    fSetTargetDensity.AvailableForStates(G4State_PreInit);

    fSetTemperature.SetParameterName("temperature", false);
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
