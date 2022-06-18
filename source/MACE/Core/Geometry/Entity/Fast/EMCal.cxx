#include "MACE/Core/Geometry/Description/EMCal.hxx"
#include "MACE/Core/Geometry/Entity/Fast/EMCal.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void EMCal::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::EMCal::Instance();
    const auto name = description.GetName();
    const auto innerRadius = description.GetInnerRadius();
    const auto innerLength = description.GetInnerLength();
    const auto windowRadius = description.GetWindowRadius();
    const auto crystalLength = description.GetCrystalLength();

    auto body = Make<G4Tubs>(
        "_temp",
        innerRadius,
        innerRadius + crystalLength,
        innerLength / 2,
        0,
        twopi);
    auto front = Make<G4Tubs>(
        "_temp",
        windowRadius,
        innerRadius + crystalLength,
        crystalLength / 2,
        0,
        twopi);
    auto back = Make<G4Tubs>(
        "_temp",
        0,
        innerRadius + crystalLength,
        crystalLength / 2,
        0,
        twopi);
    auto temp = Make<G4UnionSolid>(
        "_temp",
        body,
        front,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, -innerLength / 2 - crystalLength / 2)));
    auto solid = Make<G4UnionSolid>(
        name,
        temp,
        back,
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, innerLength / 2 + crystalLength / 2)));
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother()->GetLogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
