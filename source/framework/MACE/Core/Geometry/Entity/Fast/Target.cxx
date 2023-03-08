#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Core/Geometry/Entity/Fast/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

using MACE::Core::Geometry::Entity::Fast::Target;
using namespace MACE::Utility::LiteralUnit::Density;

void Target::Construct(G4bool checkOverlaps) {
    const auto& description = Description::Target::Instance();
    const auto& name = description.GetName();
    switch (description.ShapeType()) {
    case Description::Target::TargetShapeType::Cuboid:
        const auto& cuboidDescription = description.Cuboid();
        const auto width = cuboidDescription.Width();
        const auto thickness = cuboidDescription.Thickness();
        const auto transform = cuboidDescription.CalcTransform();
        auto solid = Make<G4Box>(
            name,
            width / 2,
            width / 2,
            thickness / 2);
        auto logic = Make<G4LogicalVolume>(
            solid,
            nullptr,
            name);
        Make<G4PVPlacement>(
            transform,
            logic,
            name,
            Mother().LogicalVolume().get(),
            false,
            0,
            checkOverlaps);
        return;
    }
}
