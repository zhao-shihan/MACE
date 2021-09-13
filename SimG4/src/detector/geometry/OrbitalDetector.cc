#include "G4Box.hh"
#include "detector/geometry/OrbitalDetector.hh"

MACE::SimG4::Geometry::OrbitalDetector::OrbitalDetector() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::OrbitalDetector::Create(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("OrbitalDetector");
    auto solid = new G4Box(name, 0.5 * fWidth, 0.5 * fWidth, 0.5 * fThickness);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}