#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerField.hxx"
#include "Geometry/Description/DescendantsOfWorld/SpectrometerField.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SpectrometerField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerField::Instance();
    auto name = description.GetName();
    auto length = description.GetLength();
    auto raidus = description.GetRadius();

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
        G4Transform3D(),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
