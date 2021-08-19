#include "G4Tubs.hh"
#include "detector/geometry/OrbitalDetectorShellField.hh"

MACE::SimG4::Geometry::OrbitalDetectorShellField::OrbitalDetectorShellField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::OrbitalDetectorShellField::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("OrbitalDetectorShellField");
    auto solid = new G4Tubs(name, 0, fRadius, 0.5 * fLength, 0, 2 * M_PI);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(0, 1, 0), M_PI_2), G4ThreeVector(fUpXPosition + 0.5 * fLength, 0, fCenterZ)), name, logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}