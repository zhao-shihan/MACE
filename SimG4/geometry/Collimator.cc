#include "G4Tubs.hh"
#include "SimG4/geometry/Collimator.hh"

MACE::SimG4::Geometry::Collimator::Collimator() :
    MACE::SimG4::Geometry::BaseInterface(8) {}

void MACE::SimG4::Geometry::Collimator::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("Collimator");
    for (size_t i = 0; i < GetVolumeSetCount(); ++i) {
        G4double radii = fInnerRadius + i * (fOuterRadius - fInnerRadius) / (GetVolumeSetCount() - 1);
        auto soild = new G4Tubs(name, radii, radii + fThickness, 0.5 * fLength, 0, 2 * M_PI);
        auto logic = new G4LogicalVolume(soild, material, name);
        auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, fZPosition), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
        GetVolumeSet().Set(soild, logic, physic);
    }
}