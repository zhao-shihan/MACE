#include "G4Tubs.hh"
#include "detector/geometry/ParallelTransportField.hh"

MACE::Geometry::ParallelTransportField::ParallelTransportField() :
    MACE::Geometry::Base(1) {}

void MACE::Geometry::ParallelTransportField::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("ParallelTransportField");
    auto solid = new G4Tubs(name, 0, fRadius, 0.5 * fLength, 0, 2 * M_PI);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, fUpZPosition + 0.5 * fLength), name, logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}