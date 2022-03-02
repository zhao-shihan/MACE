#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondTransportField.hxx"
#include "Geometry/Description/DescendantsOfWorld/SecondTransportField.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SecondTransportField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SecondTransportField::Instance();
    auto name = description.GetName();
    auto length = description.GetLength();
    auto radius = description.GetRadius();
    auto transform = description.GetTransform();

    auto solid = Make<G4Tubs>(
        name,
        0,
        radius,
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
