#include "G4Box.hh"

#include "detector/geometry/Target.hh"

MACE::Geometry::Target::Target() :
    MACE::Geometry::Base(1) {}

void MACE::Geometry::Target::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("Target");
    auto solid = new G4Box(name, 0.5 * fWidth, 0.5 * fWidth, 0.5 * fThickness);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, fDownZPosition - 0.5 * fThickness), name, logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}