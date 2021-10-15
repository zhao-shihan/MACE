#include "G4Polycone.hh"

#include "SimG4/Geometry/Spectrometer.hh"

using namespace MACE::SimG4::Geometry;

Spectrometer::Spectrometer() :
    BaseInterface(1) {}

Spectrometer::~Spectrometer() {}

void Spectrometer::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("SpectrometerShell");
    const G4double zPlane[] = { -fGasOuterLength / 2 - fShellSideThickness, -fGasInnerLength / 2 - fShellSideThickness, fGasInnerLength / 2 + fShellSideThickness, fGasOuterLength / 2 + fShellSideThickness };
    const G4double rInner[] = { fGasOuterRadius - fShellInnerThickness, fGasInnerRadius - fShellInnerThickness, fGasInnerRadius - fShellInnerThickness, fGasOuterRadius - fShellInnerThickness };
    const G4double rOuter[] = { fGasOuterRadius + fShellOuterThickness, fGasOuterRadius + fShellOuterThickness, fGasOuterRadius + fShellOuterThickness, fGasOuterRadius + fShellOuterThickness };
    auto solid = new G4Polycone(name, 0, 2 * pi, 4, zPlane, rInner, rOuter);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}