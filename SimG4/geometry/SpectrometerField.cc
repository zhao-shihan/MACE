#include "G4Tubs.hh"

#include "SimG4/geometry/SpectrometerField.hh"

MACE::SimG4::Geometry::SpectrometerField::SpectrometerField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::SpectrometerField::Create(G4Material* material, const BaseInterface* mother) {
    auto solid = new G4Tubs("SpectrometerField", 0, fRadius, 0.5 * fLength, 0, 2 * M_PI);
    auto logic = new G4LogicalVolume(solid, material, solid->GetName());
    auto physic = new G4PVPlacement(G4Transform3D(), solid->GetName(), logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}
