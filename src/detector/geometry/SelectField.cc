#include "G4Box.hh"
#include "detector/geometry/SelectField.hh"

MACE::Geometry::SelectField::SelectField() :
    MACE::Geometry::Base(1) {}

void MACE::Geometry::SelectField::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("SelectField");
    auto solid = new G4Box(name, 0.5 * fWidth, 0.5 * fWidth, 0.5 * fLength);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}