#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SelectorField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SelectorField::Instance();
    const auto name = description.GetName();
    const auto raidus = description.GetRadius();
    const auto length = description.GetLength();
    const auto zPosition = description.GetZPosition();

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
    Make<G4PVPlacement>(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, zPosition)),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
