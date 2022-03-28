#include "Core/Geometry/Description/AcceleratorField.hxx"
#include "Core/Geometry/Entity/Fast/AcceleratorField.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Geometry::Entity::Fast::AcceleratorField;

void AcceleratorField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::AcceleratorField::Instance();
    const auto name = description.GetName();
    const auto radius = description.GetRadius();
    const auto length = description.GetLength();
    const auto transform = description.GetTransform();

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
