#include "G4Tubs.hh"
#include "detector/geometry/Collimator.hh"

MACE::SimG4::Geometry::Collimator::Collimator() :
    MACE::SimG4::Geometry::BaseInterface(8) {}

void MACE::SimG4::Geometry::Collimator::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("Collimator");
    for (size_t i = 0; i < GetVolumeSetCount(); ++i) {
        G4double radii = fInnerRadius + i * (fOuterRadius - fInnerRadius) / (GetVolumeSetCount() - 1);
        auto soild = new G4Tubs(name, radii, radii + fThickness, 0.5 * fLength, 0, 2 * M_PI);
        auto logic = new G4LogicalVolume(soild, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother, false, 0, checkOverlaps);
        GetVolumeSet().Set(soild, logic, physic);
    }
}