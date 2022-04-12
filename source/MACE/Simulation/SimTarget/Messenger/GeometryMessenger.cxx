#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Core/Geometry/Description/World.hxx"
#include "MACE/Simulation/SimTarget/Messenger/GeometryMessenger.hxx"

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
    fSetTargetThickness("/MACE/Geometry/SetTargetThickness", this) {

    fDirectory.SetGuidance("SimTarget geometry controller.");

    fSetWorldHalfExtent.SetParameterName("half x", "half y", "half z", false);
    fSetWorldHalfExtent.AvailableForStates(G4State_PreInit);

    fSetTargetWidth.SetParameterName("Target width", false);
    fSetTargetWidth.AvailableForStates(G4State_PreInit);

    fSetTargetThickness.SetParameterName("Target thickness", false);
    fSetTargetThickness.AvailableForStates(G4State_PreInit);
}

void GeometryMessenger::SetNewValue(G4UIcommand* command, G4String value) {
    using namespace Core::Geometry::Description;
    if (command == std::addressof(fSetWorldHalfExtent)) {
        auto& world = World::Instance();
        auto halfExtent = fSetWorldHalfExtent.GetNew3VectorValue(value);
        world.SetHalfXExtent(halfExtent.x());
        world.SetHalfYExtent(halfExtent.y());
        world.SetHalfZExtent(halfExtent.z());
    } else if (command == std::addressof(fSetTargetWidth)) {
        Target::Instance().SetWidth(fSetTargetWidth.GetNewDoubleValue(value));
    } else if (command == std::addressof(fSetTargetThickness)) {
        Target::Instance().SetThickness(fSetTargetThickness.GetNewDoubleValue(value));
    }
}

} // namespace MACE::Simulation::SimTarget::Messenger
