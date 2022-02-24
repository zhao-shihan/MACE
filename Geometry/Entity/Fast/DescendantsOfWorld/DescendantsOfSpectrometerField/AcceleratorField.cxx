#include "G4Box.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"

using namespace MACE::Geometry::Entity::Fast;

void AcceleratorField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::AcceleratorField::Instance();
    const auto name = description.GetName();
    const auto width = description.GetWidth();
    const auto upStreamLength = description.GetUpStreamLength();
    const auto downStreamLength = description.GetDownStreamLength();

    auto material = Mother()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial();

    auto solid = Make<G4Box>(
        name,
        width / 2,
        width / 2,
        (upStreamLength + downStreamLength) / 2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        material,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0, 0, (downStreamLength - upStreamLength) / 2)),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
