#include "Core/Geometry/Description/EMCal.hxx"
#include "Core/Geometry/Entity/Fast/EMCal.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

using MACE::Core::Geometry::Entity::Fast::EMCal;

void EMCal::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::EMCal::Instance();
    const auto name = description.GetName();
    const auto innerRadius = description.GetInnerRadius();
    const auto innerLength = description.GetInnerLength();
    const auto windowRadius = description.GetWindowRadius();
    const auto crystalLength = description.GetCrystalLength();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_CESIUM_IODIDE");

    auto body = Make<G4Tubs>(
        "_temp",
        innerRadius,
        innerRadius + crystalLength,
        innerLength / 2,
        0,
        2 * M_PI);
    auto front = Make<G4Tubs>(
        "_temp",
        windowRadius,
        innerRadius + crystalLength,
        crystalLength / 2,
        0,
        2 * M_PI);
    auto back = Make<G4Tubs>(
        "_temp",
        0,
        innerRadius + crystalLength,
        crystalLength / 2,
        0,
        2 * M_PI);
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
        material,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
