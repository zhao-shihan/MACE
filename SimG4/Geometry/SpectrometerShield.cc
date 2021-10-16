#include "G4Tubs.hh"
#include "G4UnionSolid.hh"
#include "SimG4/Geometry/SpectrometerShield.hh"

using namespace MACE::SimG4::Geometry;

SpectrometerShield::SpectrometerShield() :
    BaseInterface(1) {}

void SpectrometerShield::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("SpectrometerShield");
    auto body = new G4Tubs(name + "Body", fInnerRadius, fInnerRadius + fThickness, 0.5 * fInnerLength, 0, 2 * M_PI);
    auto cap = new G4Tubs(name + "Cap", fWindowRadius, fInnerRadius + fThickness, 0.5 * fThickness, 0, 2 * M_PI);
    auto temp = new G4UnionSolid("_temp", body, cap, G4Transform3D(G4RotationMatrix(), G4ThreeVector(0, 0, -0.5 * fInnerLength - 0.5 * fThickness)));
    auto solid = new G4UnionSolid(name, temp, cap, G4Transform3D(G4RotationMatrix(), G4ThreeVector(0, 0, 0.5 * fInnerLength + 0.5 * fThickness)));
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother->GetPhysicalVolume(), false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}
