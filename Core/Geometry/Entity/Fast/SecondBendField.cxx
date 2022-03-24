#include "Geometry/Description/SecondBendField.hxx"
#include "Geometry/Entity/Fast/SecondBendField.hxx"

#include "G4PVPlacement.hh"
#include "G4Torus.hh"

using MACE::Geometry::Entity::Fast::SecondBendField;

void SecondBendField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SecondBendField::Instance();
    auto name = description.GetName();
    auto raidus = description.GetRadius();
    auto bendRadius = description.GetBendRadius();
    auto transform = description.GetTransform();

    auto solid = Make<G4Torus>(
        name,
        0,
        raidus,
        bendRadius,
        -M_PI_2,
        M_PI_2);
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
