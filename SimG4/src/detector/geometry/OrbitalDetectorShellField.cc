#include "G4Tubs.hh"
#include "detector/geometry/OrbitalDetectorShellField.hh"

MACE::SimG4::Geometry::OrbitalDetectorShellField::OrbitalDetectorShellField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::OrbitalDetectorShellField::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("OrbitalDetectorShellField");
    auto solid = new G4Tubs(name, 0.0, fRadius, 0.5 * fLength, 0.0, 2.0 * M_PI);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(nullptr, G4ThreeVector(fCenterX, 0.0, fUpZPosition + 0.5 * fLength), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}