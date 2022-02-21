#include "G4Torus.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendField.hxx"
#include "Geometry/Description/DescendantsOfWorld/FirstBendField.hxx"

using namespace MACE::Geometry::Entity::Fast;

void FirstBendField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::FirstBendField::Instance();
    auto name = description.GetName();
    auto raidus = description.GetRaidus();
    auto bendRadius = description.GetBendRadius();
    auto xPosition = description.GetXPosition();
    auto zPosition = description.GetZPosition();

    auto material = Mother()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial();

    auto solid = Make<G4Torus>(
        name,
        0,
        raidus,
        bendRadius,
        M_PI_2,
        M_PI_2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        material,
        name);
    auto physics = Make<G4PVPlacement>(
        G4Transform3D(
            G4RotationMatrix(G4ThreeVector(1, 0, 0), M_PI_2),
            G4ThreeVector(xPosition, 0, zPosition)),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
