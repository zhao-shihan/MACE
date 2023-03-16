#include "MACE/Detector/Description/Collimator.hxx"
#include "MACE/Detector/Geometry/Fast/Collimator.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace MACE::PhysicalConstant;

void Collimator::Construct(G4bool checkOverlaps) {
    const auto& description = Description::Collimator::Instance();
    const auto name = description.GetName();
    const auto innerRadius = description.InnerRadius();
    const auto outerRadius = description.OuterRadius();
    const auto length = description.Length();
    const auto thickness = description.Thickness();
    const auto axialPosition = description.AxialPosition();
    const auto count = description.Count();

    for (int i = 0; i < count; ++i) {
        auto radii = innerRadius + i * (outerRadius - innerRadius) / (count - 1);
        auto solid = Make<G4Tubs>(
            name,
            radii,
            radii + thickness,
            length / 2,
            0,
            twopi);
        auto logic = Make<G4LogicalVolume>(
            solid,
            nullptr,
            name);
        Make<G4PVPlacement>(
            G4Transform3D(
                G4RotationMatrix(),
                G4ThreeVector(0.0, 0.0, axialPosition)),
            logic,
            name,
            Mother().LogicalVolume().get(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Detector::Geometry::Fast
