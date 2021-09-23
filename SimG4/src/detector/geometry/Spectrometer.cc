#include "G4Polycone.hh"

#include "detector/geometry/Spectrometer.hh"

using namespace MACE::SimG4::Geometry;

Spectrometer::Spectrometer() :
    BaseInterface(1) {}

Spectrometer::~Spectrometer() {}

void Spectrometer::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("Spectrometer");
    const G4double zPlane[] = { -fOuterLength / 2, -fInnerLength / 2, fInnerLength / 2, fOuterLength / 2 };
    const G4double rInner[] = { fOuterRadius, fInnerRadius, fInnerRadius, fOuterRadius };
    const G4double rOuter[] = { fOuterRadius, fOuterRadius, fOuterRadius, fOuterRadius };
    auto solid = new G4Polycone(name, 0, 2 * pi, 4, zPlane, rInner, rOuter);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}