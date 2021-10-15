#include "G4Box.hh"

#include "SimG4/Geometry/AcceleratorField.hh"

MACE::SimG4::Geometry::AcceleratorField::AcceleratorField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::AcceleratorField::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("AcceleratorField");
    auto solid = new G4Box(name, 0.5 * fWidth, 0.5 * fWidth, 0.5 * (fUpStreamLength + fDownStreamLength));
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0.5 * (fDownStreamLength - fUpStreamLength)), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}