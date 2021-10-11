#include "G4Tubs.hh"
#include "SimG4/geometry/Calorimeter.hh"

MACE::SimG4::Geometry::Calorimeter::Calorimeter() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::Calorimeter::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("Calorimeter");
    auto solid = new G4Tubs(name, fInnerRadius, fOuterRadius, 0.5 * fLength, 0, 2 * M_PI);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}
