#include "G4Box.hh"
#include "detector/geometry/TurnField.hh"

MACE::SimG4::Geometry::TurnField::TurnField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::TurnField::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("TurnField");
    auto solid = new G4Box(name, 0.5 * fWidth, fHalfHeight, 0.5 * fWidth);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, fUpZPosition + 0.5 * fWidth), name, logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}
