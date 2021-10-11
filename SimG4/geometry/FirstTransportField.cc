#include "G4Tubs.hh"
#include "SimG4/geometry/FirstTransportField.hh"

MACE::SimG4::Geometry::FirstTransportField::FirstTransportField() :
    MACE::SimG4::Geometry::BaseInterface(1) {}

void MACE::SimG4::Geometry::FirstTransportField::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("FirstTransportField");
    auto solid = new G4Tubs(name, 0, fRadius, 0.5 * fLength, 0, 2 * M_PI);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, fUpZPosition + 0.5 * fLength), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}