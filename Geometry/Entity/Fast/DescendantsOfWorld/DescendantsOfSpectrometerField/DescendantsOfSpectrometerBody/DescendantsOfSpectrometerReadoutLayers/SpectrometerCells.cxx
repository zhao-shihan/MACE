#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/SpectrometerCells.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayers/SpectrometerCells.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SpectrometerCells::ConstructSelf(G4bool checkOverlaps) {
    const auto& layersDescription = Description::SpectrometerReadoutLayers::Instance();
    const auto layerInfoList = layersDescription.GetInformationList();
    const auto layerThick = layersDescription.GetThickness();

    const auto& cellsDescription = Description::SpectrometerCells::Instance();
    const auto name = cellsDescription.GetName();
    const auto cellInfoList = cellsDescription.GetInformationList();
    const auto cellCount = cellInfoList.size();

    for (size_t cellID = 0; cellID < cellCount; ++cellID) {
        auto&& [layerID, cellAngle, cellPhi] = cellInfoList[cellID];
        auto&& [layerRadius, halfLength] = layerInfoList[layerID];
        auto solid = Make<G4Tubs>(
            name,
            layerRadius - layerThick / 2,
            layerRadius + layerThick / 2,
            halfLength,
            cellPhi - cellAngle / 2,
            cellAngle);
        auto logic = Make<G4LogicalVolume>(
            solid,
            Mother()->GetMaterial(layerID),
            name);
        Make<G4PVPlacement>(
            G4Transform3D(),
            name,
            logic,
            Mother()->GetPhysicalVolume(layerID),
            true,
            cellID,
            checkOverlaps);
    }
}
