#include "G4Box.hh"

#include "detector/geometry/World.hh"

MACE::SimG4::Geometry::World::World() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::World::Create(G4Material* material, const BaseInterface*) {
    auto solid = new G4Box("World", fHalfXExtent, fHalfYExtent, fHalfZExtent);
    auto logic = new G4LogicalVolume(solid, material, solid->GetName());
    auto physic = new G4PVPlacement(G4Transform3D(), solid->GetName(), logic, nullptr, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}