#include "MACE/Detector/Description/Target.hxx"
#include "MACE/Detector/Geometry/Fast/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

using MACE::Detector::Geometry::Fast::Target;
using namespace MACE::LiteralUnit::Density;

void Target::Construct(G4bool checkOverlaps) {
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
