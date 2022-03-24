#include "Geometry/Description/SpectrometerField.hxx"
#include "Geometry/Entity/Fast/SpectrometerField.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Geometry::Entity::Fast::SpectrometerField;

void SpectrometerField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerField::Instance();
    auto name = description.GetName();
    auto length = description.GetLength();
    auto raidus = description.GetRadius();

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
        G4Transform3D(),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
