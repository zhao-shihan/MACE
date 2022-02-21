#include "G4Tubs.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"

using namespace MACE::Geometry::Entity::Fast;

SpectrometerCells::SpectrometerCells() :
    fCellLayerIDAndPositionList(0) {}

void SpectrometerCells::ConstructSelf(G4bool checkOverlaps) {
    const auto& cellsDescription = Description::SpectrometerCells::Instance();
    const auto& layersDescription = Description::SpectrometerReadoutLayers::Instance();
    const auto name = cellsDescription.GetName();
    // const auto rSenseWire = cellsDescription.GetSenseWireDiameter() / 2;
    const auto rFieldWire = cellsDescription.GetFieldWireDiameter() / 2;
    const auto cellWidth = layersDescription.GetAverageCellWidth();

    auto material = Mother()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial();

    int cellId = 0;
    fCellLayerIDAndPositionList.clear();
    for (int layerId = 0; layerId < Mother()->GetPhysicalVolumeNum(); ++layerId) {
        auto motherVolume = Mother()->GetPhysicalVolume(layerId);
        const auto motherSolid = static_cast<const G4Tubs*>(motherVolume->GetLogicalVolume()->GetSolid());
        const auto halfLength = motherSolid->GetZHalfLength();
        const auto layerInnerRadius = motherSolid->GetInnerRadius();
        const auto layerOuterRadius = motherSolid->GetOuterRadius();
        const auto layerCenterRadius = (layerInnerRadius + layerOuterRadius) / 2;

        const int cellCount = 4 * std::lround(M_PI_2 / (2 * std::asin(0.5 * cellWidth / layerCenterRadius)));
        const auto cellAngle = 2 * M_PI / cellCount;
        const auto gapHalfAngle = rFieldWire / layerInnerRadius;
        auto solid = Make<G4Tubs>(
            name,
            layerInnerRadius + rFieldWire,
            layerOuterRadius,
            halfLength,
            gapHalfAngle,
            cellAngle - 2 * gapHalfAngle);
        auto logic = Make<G4LogicalVolume>(
            solid,
            material,
            name);
        for (int k = 0; k < cellCount; ++k) {
            auto cellPhi = k * cellAngle;
            auto physics = Make<G4PVPlacement>(
                G4Transform3D(
                    G4RotationMatrix(G4ThreeVector(0.0, 0.0, 1.0), cellPhi),
                    G4ThreeVector()),
                name,
                logic,
                motherVolume,
                true,
                cellId,
                checkOverlaps);

            auto cellX = layerCenterRadius * std::cos(cellPhi);
            auto cellY = layerCenterRadius * std::sin(cellPhi);
            auto cellPosition = G4TwoVector(cellX, cellY);
            fCellLayerIDAndPositionList.emplace_back(layerId, cellPosition);
            ++cellId;
        }
    }
}
