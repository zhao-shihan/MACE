#include "Geometry/Description/SpectrometerCells.hxx"
#include "Geometry/Description/SpectrometerReadoutLayers.hxx"
#include "Geometry/Entity/Fast/SpectrometerCells.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Geometry::Entity::Fast::SpectrometerCells;

void SpectrometerCells::ConstructSelf(G4bool checkOverlaps) {
    const auto& layersDescription = Description::SpectrometerReadoutLayers::Instance();
    const auto layerInfoList = layersDescription.GetInformationList();
    const auto layerCount = layerInfoList.size();

    const auto& cellsDescription = Description::SpectrometerCells::Instance();
    const auto name = cellsDescription.GetName();
    const auto cellInfoList = cellsDescription.GetInformationList();

    for (size_t cellID = 0, layerID = 0; layerID < layerCount; ++layerID) {
        auto&& [cellRadius, cellWidth, halfLength, _0] = layerInfoList[layerID];
        auto&& [cellAngle, _1, rotations] = cellInfoList[layerID];
        auto solid = Make<G4Tubs>(
            name,
            cellRadius - cellWidth / 2,
            cellRadius + cellWidth / 2,
            halfLength,
            0,
            cellAngle);
        auto logic = Make<G4LogicalVolume>(
            solid,
            Mother()->GetMaterial(layerID),
            name);
        for (auto&& rotation : rotations) {
            Make<G4PVPlacement>(
                G4Transform3D(
                    rotation,
                    G4ThreeVector()),
                logic,
                name,
                Mother()->GetLogicalVolume(layerID),
                false,
                cellID,
                checkOverlaps);
            ++cellID;
        }
    }
}
