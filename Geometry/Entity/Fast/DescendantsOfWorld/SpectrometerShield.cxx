#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerShield.hxx"
#include "Geometry/Description/DescendantsOfWorld/SpectrometerShield.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SpectrometerShield::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerShield::Instance();
    auto name = description.GetName();
    auto innerRadius = description.GetInnerRadius();
    auto innerLength = description.GetInnerLength();
    auto windowRadius = description.GetWindowRadius();
    auto thickness = description.GetThickness();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Fe");

    auto body = Make<G4Tubs>(
        "_temp",
        innerRadius,
        innerRadius + thickness,
        innerLength / 2,
        0,
        2 * M_PI);
    auto cap = Make<G4Tubs>(
        "_temp",
        windowRadius,
        innerRadius + thickness,
        thickness / 2,
        0,
        2 * M_PI);
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
        material,
        name);
    auto physics = Make<G4PVPlacement>(
        G4Transform3D(),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
