#include "MACE/Core/Geometry/Description/SelectorField.hxx"
#include "MACE/Core/Geometry/Entity/Fast/SelectorField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void SelectorField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SelectorField::Instance();
    const auto name = description.GetName();
    const auto radius = description.GetRadius();
    const auto length = description.GetLength();
    const auto zPosition = description.GetAxialPosition();

    auto solid = Make<G4Tubs>(
        name,
        0,
        radius,
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
            G4ThreeVector(0, 0, zPosition)),
        logic,
        name,
        Mother()->GetLogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
