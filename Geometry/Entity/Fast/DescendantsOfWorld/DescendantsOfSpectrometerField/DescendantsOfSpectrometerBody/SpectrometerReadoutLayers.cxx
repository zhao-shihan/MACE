#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SpectrometerReadoutLayers::ConstructSelf(G4bool checkOverlaps) {
    const auto& layersDescription = Description::SpectrometerReadoutLayers::Instance();
    const auto& bodyDescription = Description::SpectrometerBody::Instance();
    const auto name = layersDescription.GetName();
    const auto layerThickness = layersDescription.GetAverageCellWidth();
    const auto gasInnerRadius = bodyDescription.GetGasInnerRadius();
    const auto gasOuterRadius = bodyDescription.GetGasOuterRadius();
    const auto gasInnerLength = bodyDescription.GetGasInnerLength();
    const auto gasOuterLength = bodyDescription.GetGasOuterLength();

    const auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_He");

    const auto sideSlope = (gasOuterLength / 2 - gasInnerLength / 2) / (gasOuterRadius - gasInnerRadius);
    const int layerCount = std::floor((gasOuterRadius - gasInnerRadius) / layerThickness);
    for (int i = 0; i < layerCount; ++i) {
        const auto halfLength = gasInnerLength / 2 + i * layerThickness * sideSlope;
        const auto layerCenterRadius = gasInnerRadius + (i + 0.5) * layerThickness;
        auto solid = Make<G4Tubs>(
            name,
            layerCenterRadius - layerThickness / 2,
            layerCenterRadius + layerThickness / 2,
            halfLength,
            0,
            2 * M_PI);
        auto logic = Make<G4LogicalVolume>(
            solid,
            material,
            name);
        auto physics = Make<G4PVPlacement>(
            G4Transform3D(),
            name,
            logic,
            Mother()->GetPhysicalVolume(),
            true,
            i,
            checkOverlaps);
    }
}
