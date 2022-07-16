#include "MACE/Core/Geometry/Description/EMCalShield.hxx"
#include "MACE/Core/Geometry/Entity/Fast/EMCalShield.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void EMCalShield::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::EMCalShield::Instance();
    auto name = description.GetName();
    auto innerRadius = description.GetInnerRadius();
    auto innerLength = description.GetInnerLength();
    auto windowRadius = description.GetWindowRadius();
    auto thickness = description.GetThickness();
    auto transform = description.CalcTransform();

    auto body = Make<G4Tubs>(
        "_temp",
        innerRadius,
        innerRadius + thickness,
        innerLength / 2,
        0,
        twopi);
    auto cap = Make<G4Tubs>(
        "_temp",
        windowRadius,
        innerRadius + thickness,
        thickness / 2,
        0,
        twopi);
    auto temp = Make<G4UnionSolid>(
        "_temp",
        body,
        cap,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, -innerLength / 2 - thickness / 2)));
    auto solid = Make<G4UnionSolid>(
        name,
        temp,
        cap,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, innerLength / 2 + thickness / 2)));
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        transform,
        logic,
        name,
        Mother()->GetLogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
