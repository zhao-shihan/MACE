#include "G4Tubs.hh"

#include "detector/geometry/SpectrometerReadOutLayer.hh"
#include "detector/geometry/Spectrometer.hh"

using namespace MACE::SimG4::Geometry;

SpectrometerReadOutLayer::SpectrometerReadOutLayer() :
    BaseInterface(0) {}

SpectrometerReadOutLayer::~SpectrometerReadOutLayer() {}

void SpectrometerReadOutLayer::Create(G4Material* material, const BaseInterface* mother) {
    const auto* spectrometer = static_cast<const Spectrometer*>(mother);
    auto outerRadius = spectrometer->GetOuterRadius();
    auto innerRadius = spectrometer->GetInnerRadius();
    auto outerLength = spectrometer->GetOuterLength();
    auto innerLength = spectrometer->GetInnerLength();

    ResizeVolumeSetList(size_t((outerRadius - innerRadius) / fLayerPitch) - 1);
    G4String name("Spectrometer");
    for (size_t i = 0; i < GetVolumeSetCount(); ++i) {
        G4double radii = innerRadius + (i + 1) * fLayerPitch;
        G4double halfActiveLength = 0.5 * (innerLength + i * (outerLength - innerLength) / (GetVolumeSetCount() + 1));
        auto solid = new G4Tubs(name, radii, radii + 1 * mm, halfActiveLength, 0. * deg, 360. * deg);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(), name, logic, spectrometer->GetPhysicalVolume(), true, i, checkOverlaps);
        GetVolumeSet(i).Set(solid, logic, physic);
    }
}