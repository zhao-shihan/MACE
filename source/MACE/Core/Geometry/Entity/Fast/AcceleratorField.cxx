#include "MACE/Core/Geometry/Description/AcceleratorField.hxx"
#include "MACE/Core/Geometry/Entity/Fast/AcceleratorField.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::AcceleratorField;

void AcceleratorField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::AcceleratorField::Instance();
    const auto name = description.GetName();
    const auto radius = description.GetRadius();
    const auto length = description.GetLength();
    const auto transform = description.CalcTransform();

    auto solid = Make<G4Tubs>(
        name,
        0,
        radius,
        length / 2,
        0,
        2 * M_PI);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        transform,
        logic,
        name,
        Mother()->GetLogicalVolume(),
        false,
        0,
        checkOverlaps);
}
