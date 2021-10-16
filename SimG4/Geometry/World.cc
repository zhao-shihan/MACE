#include "G4Box.hh"
#include "G4GDMLParser.hh"

#include "SimG4/Geometry/World.hh"

using namespace MACE::SimG4::Geometry;

World::World() :
    BaseInterface(1) {}

void World::Create(G4Material* material, const BaseInterface*) {
    auto solid = new G4Box("World", fHalfXExtent, fHalfYExtent, fHalfZExtent);
    auto logic = new G4LogicalVolume(solid, material, solid->GetName());
    auto physic = new G4PVPlacement(G4Transform3D(), solid->GetName(), logic, nullptr, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}

void World::WriteGDML() {
    G4GDMLParser gdml;
    gdml.SetOutputFileOverwrite(true);
    gdml.Write("MACEGeometry.gdml", GetPhysicalVolume());
}