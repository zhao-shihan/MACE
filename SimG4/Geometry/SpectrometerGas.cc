#include "G4Polycone.hh"
#include "G4SubtractionSolid.hh"

#include "SimG4/Geometry/SpectrometerGas.hh"

using namespace MACE::SimG4::Geometry;

SpectrometerGas::SpectrometerGas() :
    BaseInterface(1) {}

SpectrometerGas::~SpectrometerGas() {}

void SpectrometerGas::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("SpectrometerGas");
    const G4double zPlane[] = { -fGasOuterLength / 2, -fGasInnerLength / 2, fGasInnerLength / 2, fGasOuterLength / 2 };
    const G4double rInner[] = { fGasOuterRadius, fGasInnerRadius, fGasInnerRadius, fGasOuterRadius };
    const G4double rOuter[] = { fGasOuterRadius, fGasOuterRadius, fGasOuterRadius, fGasOuterRadius };
    auto solid = new G4Polycone(name, 0, 2 * pi, 4, zPlane, rInner, rOuter);
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}