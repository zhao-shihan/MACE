#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

using MACE::Detector::Definition::Target;
using namespace MACE::LiteralUnit::Density;

auto Target::Construct(G4bool checkOverlaps) -> void {
    const auto& description = Description::Target::Instance();
    const auto& name = description.Name();
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
