#include "MACE/Core/Geometry/Description/EMCalField.hxx"
#include "MACE/Core/Geometry/Entity/Fast/EMCalField.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::EMCalField;

void EMCalField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::EMCalField::Instance();
    auto name = description.GetName();
    auto radius = description.GetRadius();
    auto length = description.GetLength();
    auto transform = description.CalcTransform();

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
