#include "G4Box.hh"

#include "detector/geometry/World.hh"

MACE::Geometry::World::World() :
    MACE::Geometry::Base(1) {}

void MACE::Geometry::World::Make(G4Material* material, G4VPhysicalVolume*) {
    auto solid = new G4Box("World", fHalfXExtent, fHalfYExtent, fHalfZExtent);
    auto logic = new G4LogicalVolume(solid, material, solid->GetName());
    auto physic = new G4PVPlacement(G4Transform3D(), solid->GetName(), logic, nullptr, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}