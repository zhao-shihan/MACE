#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportField.hxx"
#include "Geometry/Description/DescendantsOfWorld/FirstTransportField.hxx"

using namespace MACE::Geometry::Entity::Fast;

void FirstTransportField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::FirstTransportField::Instance();
    auto name = description.GetName();
    auto raidus = description.GetRaidus();
    auto length = description.GetLength();
    auto upZPosition = description.GetUpZPosition();

    auto material = Mother()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial();

    auto solid = Make<G4Tubs>(
        name,
        0,
        raidus,
        length / 2,
        0,
        2 * M_PI);
    auto logic = Make<G4LogicalVolume>(
        solid,
        material,
        name);
    auto physics = Make<G4PVPlacement>(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, upZPosition + length / 2)),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
