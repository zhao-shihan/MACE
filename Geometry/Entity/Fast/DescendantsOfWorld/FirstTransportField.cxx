#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportField.hxx"
#include "Geometry/Description/DescendantsOfWorld/FirstTransportField.hxx"

using namespace MACE::Geometry::Entity::Fast;

void FirstTransportField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::FirstTransportField::Instance();
    auto name = description.GetName();
    auto raidus = description.GetRadius();
    auto length = description.GetLength();
    auto transform = description.GetTransform();

    auto solid = Make<G4Tubs>(
        name,
        0,
        raidus,
        length / 2,
        0,
        2 * M_PI);
    auto logic = Make<G4LogicalVolume>(
        solid,
        Mother()->GetMaterial(),
        name);
    Make<G4PVPlacement>(
        transform,
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
