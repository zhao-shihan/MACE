#include "G4Tubs.hh"

#include "detector/geometry/SpectrometerField.hh"

MACE::Geometry::SpectrometerField::SpectrometerField() :
    MACE::Geometry::BaseInterface(1) {}

void MACE::Geometry::SpectrometerField::Make(G4Material* material, G4VPhysicalVolume* mother) {
    auto solid = new G4Tubs("SpectrometerField", 0, fRadius, 0.5 * fLength, 0, 2 * M_PI);
    auto logic = new G4LogicalVolume(solid, material, solid->GetName());
    auto physic = new G4PVPlacement(G4Transform3D(), solid->GetName(), logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}
