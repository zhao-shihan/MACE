#include "G4Tubs.hh"

#include "detector/geometry/Spectrometer.hh"

MACE::SimG4::Geometry::Spectrometer::Spectrometer() :
    MACE::SimG4::Geometry::BaseInterface(5) {}

void MACE::SimG4::Geometry::Spectrometer::Make(G4Material* material, G4VPhysicalVolume* mother) {
    for (size_t i = 0; i < GetVolumeSetCount(); ++i) {
        G4double radii = fInnerRadius + i * (fOuterRadius - fInnerRadius) / (GetVolumeSetCount() - 1);
        G4double halfActiveLength = 0.5 * (fInnerEffectiveLength + i * (fOuterEffectiveLength - fInnerEffectiveLength) / (GetVolumeSetCount() - 1));
        auto solid = new G4Tubs("Spectrometer", radii, radii + fThickness, halfActiveLength, 0. * deg, 360. * deg);
        auto logic = new G4LogicalVolume(solid, material, solid->GetName());
        auto physic = new G4PVPlacement(G4Transform3D(), logic->GetName(), logic, mother, true, i, checkOverlaps);
        GetVolumeSet(i).Set(solid, logic, physic);
    }
}