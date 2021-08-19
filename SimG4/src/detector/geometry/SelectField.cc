#include "G4Tubs.hh"
#include "detector/geometry/SelectField.hh"

MACE::SimG4::Geometry::SelectField::SelectField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::SelectField::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("SelectField");
    auto solid = new G4Tubs(name, 0, fRadius, 0.5 * fLength, 0, 2 * M_PI);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}