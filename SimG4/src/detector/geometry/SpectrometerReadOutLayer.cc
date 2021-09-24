#include "G4Tubs.hh"

#include "detector/geometry/SpectrometerReadOutLayer.hh"

using namespace MACE::SimG4::Geometry;

SpectrometerReadOutLayer::SpectrometerReadOutLayer() :
    BaseInterface(0) {}

SpectrometerReadOutLayer::~SpectrometerReadOutLayer() {}

void SpectrometerReadOutLayer::Create(G4Material* material, const BaseInterface* mother) {
    G4String name("Spectrometer");
    ResizeVolumeSetList(size_t((fGasOuterRadius - fGasInnerRadius) / fReadOutLayerPitch) - 1);
    for (size_t i = 0; i < GetVolumeSetCount(); ++i) {
        G4double radii = fGasInnerRadius + (i + 1) * fReadOutLayerPitch;
        G4double halfActiveLength = 0.5 * (fGasInnerLength + i * (fGasOuterLength - fGasInnerLength) / (GetVolumeSetCount() + 1));
        auto solid = new G4Tubs(name, radii, radii + 1 * mm, halfActiveLength, 0. * deg, 360. * deg);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(), name, logic, mother->GetPhysicalVolume(), true, i, checkOverlaps);
        GetVolumeSet(i).Set(solid, logic, physic);
    }
}