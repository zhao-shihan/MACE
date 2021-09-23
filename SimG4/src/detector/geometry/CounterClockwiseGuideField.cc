#include "G4Torus.hh"
#include "detector/geometry/CounterClockwiseGuideField.hh"

MACE::SimG4::Geometry::CounterClockwiseGuideField::CounterClockwiseGuideField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::CounterClockwiseGuideField::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("CounterClockwiseGuideField");
    auto solid = new G4Torus(name, 0, fRadius, fBendRadius, pi / 2, pi / 2);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(1, 0, 0), pi / 2), G4ThreeVector(fBendRadius, 0, fUpZPosition)), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}
