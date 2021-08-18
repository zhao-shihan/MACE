#include "G4Tubs.hh"
#include "G4MultiUnion.hh"
#include "detector/geometry/OrbitalDetectorShield.hh"

MACE::Geometry::OrbitalDetectorShield::OrbitalDetectorShield() :
    MACE::Geometry::BaseInterface(1) {}

void MACE::Geometry::OrbitalDetectorShield::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("OrbitalDetectorShield");
    auto body = new G4Tubs(name + "Body", fInnerRadius, fInnerRadius + fThickness, 0.5 * fInnerLength, 0, 2 * M_PI);
    auto cap = new G4Tubs(name + "Cap", fWindowRadius, fInnerRadius + fThickness, 0.5 * fThickness, 0, 2 * M_PI);
    auto solid = new G4MultiUnion(name);
    G4Transform3D noTrans;
    G4Transform3D upStreamTrans(G4RotationMatrix(), G4ThreeVector(0, 0, -0.5 * fInnerLength - 0.5 * fThickness));
    G4Transform3D downStreamTrans(G4RotationMatrix(), G4ThreeVector(0, 0, 0.5 * fInnerLength + 0.5 * fThickness));
    solid->AddNode(*body, noTrans);
    solid->AddNode(*cap, upStreamTrans);
    solid->AddNode(*cap, downStreamTrans);
    solid->Voxelize();
    auto logic = new G4LogicalVolume(solid, material, name);
    auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(0, 1, 0), M_PI_2), G4ThreeVector(fUpXPosition + 0.5 * fInnerLength, 0, fCenterZ)), name, logic, mother, false, 0, checkOverlaps);
    GetVolumeSet().Set(solid, logic, physic);
}
