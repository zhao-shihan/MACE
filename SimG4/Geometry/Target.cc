#include "G4Box.hh"

#include "SimG4/Geometry/Target.hh"

MACE::SimG4::Geometry::Target::Target() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::Target::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("Target");
    auto solid = new G4Box(name, 0.5 * fWidth, 0.5 * fWidth, 0.5 * fThickness);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, fDownZPosition - 0.5 * fThickness), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}