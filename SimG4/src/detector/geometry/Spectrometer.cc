#include "G4Tubs.hh"
#include "G4MultiUnion.hh"

#include "detector/geometry/Spectrometer.hh"

using namespace MACE::SimG4::Geometry;

Spectrometer::Spectrometer() :
    BaseInterface(8),
    fGDML(new G4GDMLParser()) {}

Spectrometer::~Spectrometer() {
    delete fGDML;
}

void Spectrometer::Make(G4Material* material, G4VPhysicalVolume* mother) {
    G4String name("Spectrometer");
    for (size_t i = 0; i < GetVolumeSetCount(); ++i) {
        G4double radii = fInnerRadius + i * (fOuterRadius - fInnerRadius) / (GetVolumeSetCount() - 1);
        G4double halfActiveLength = 0.5 * (fInnerEffectiveLength + i * (fOuterEffectiveLength - fInnerEffectiveLength) / (GetVolumeSetCount() - 1));
        auto solid = new G4Tubs(name, radii, radii + fThickness, halfActiveLength, 0. * deg, 360. * deg);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother, true, i, checkOverlaps);
        GetVolumeSet(i).Set(solid, logic, physic);
    }
    // ... then construct a temp union and write to gdml for fitter or others.
    G4MultiUnion unionSolid(name);
    G4Transform3D noTransform;
    for (size_t i = 0; i < GetVolumeSetCount(); ++i) {
        unionSolid.AddNode(*GetVolumeSet(i).GetSolidVolume(), noTransform);
    }
    unionSolid.Voxelize();
    G4LogicalVolume logicalUnion(&unionSolid, material, name);
    fGDML->SetOutputFileOverwrite(true);
    fGDML->Write("spectrometer_geometry.gdml", &logicalUnion);
}