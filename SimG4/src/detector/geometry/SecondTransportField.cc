#include "G4Tubs.hh"
#include "detector/geometry/SecondTransportField.hh"

MACE::SimG4::Geometry::SecondTransportField::SecondTransportField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::SecondTransportField::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("SecondTransportField");
    auto solid = new G4Tubs(name, 0.0, fRadius, 0.5 * fLength, 0, 2.0 * M_PI);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(0.0, 1.0, 0.0), pi / 2.0), G4ThreeVector(fUpXPosition + 0.5 * fLength, 0.0, fCenterZ)), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}
