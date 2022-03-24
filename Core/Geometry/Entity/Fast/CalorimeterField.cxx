#include "Geometry/Description/CalorimeterField.hxx"
#include "Geometry/Entity/Fast/CalorimeterField.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Geometry::Entity::Fast::CalorimeterField;

void CalorimeterField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::CalorimeterField::Instance();
    auto name = description.GetName();
    auto radius = description.GetRadius();
    auto length = description.GetLength();
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
