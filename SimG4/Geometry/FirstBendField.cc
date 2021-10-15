#include "G4Torus.hh"
#include "G4MultiUnion.hh"
#include "SimG4/Geometry/FirstBendField.hh"

MACE::SimG4::Geometry::FirstBendField::FirstBendField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::FirstBendField::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("FirstBendField");
    auto solid = new G4Torus(name, 0, fRadius, fBendRadius, pi / 2.0, pi / 2.0);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(1.0, 0.0, 0.0), pi / 2.0), G4ThreeVector(fXPosition, 0.0, fZPosition)), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}
