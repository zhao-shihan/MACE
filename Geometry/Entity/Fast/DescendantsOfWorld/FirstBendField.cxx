#include "G4Torus.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendField.hxx"
#include "Geometry/Description/DescendantsOfWorld/FirstBendField.hxx"

using namespace MACE::Geometry::Entity::Fast;

void FirstBendField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::FirstBendField::Instance();
    auto name = description.GetName();
    auto raidus = description.GetRadius();
    auto bendRadius = description.GetBendRadius();
    auto transform = description.GetTransform();

    auto solid = Make<G4Torus>(
        name,
        0,
        raidus,
        bendRadius,
        M_PI_2,
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
