#include "G4Box.hh"

#include "detector/geometry/AcceleratorField.hh"

MACE::Geometry::AcceleratorField::AcceleratorField() :
    MACE::Geometry::Base(1) {}

void MACE::Geometry::AcceleratorField::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("AcceleratorField");
    auto solid = new G4Box(name, 0.5 * fWidth, 0.5 * fWidth, 0.5 * (fUpStreamLength + fDownStreamLength));
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0.5 * (fDownStreamLength - fUpStreamLength)), name, logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}