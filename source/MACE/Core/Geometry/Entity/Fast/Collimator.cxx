#include "MACE/Core/Geometry/Description/Collimator.hxx"
#include "MACE/Core/Geometry/Entity/Fast/Collimator.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void Collimator::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::Collimator::Instance();
    const auto name = description.GetName();
    const auto innerRadius = description.GetInnerRadius();
    const auto outerRadius = description.GetOuterRadius();
    const auto length = description.GetLength();
    const auto thickness = description.GetThickness();
    const auto zPosition = description.GetZPosition();
    const auto count = description.GetCount();

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
                G4ThreeVector(0.0, 0.0, zPosition)),
            logic,
            name,
            Mother()->GetLogicalVolume(),
            false,
            0,
            checkOverlaps);
    }
}

} // namespace MACE::Core::Geometry::Entity::Fast
