#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerCells final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SpectrometerCells, MACE::Geometry::Description::SpectrometerReadoutLayer> {
public:
    SpectrometerCells() : fCellLayerIDAndPositionList(0) {}
    ~SpectrometerCells() noexcept = default;

    const auto& GetLayerIdAndPosition(G4int cellId) const { return fCellLayerIDAndPositionList[cellId]; }

private:
    enum { kSpectrometerCells, kSpectrometerReadoutLayer };
    void ConstructSelf() override {
        const auto name = GetDescription<kSpectrometerCells>().GetName();
        // const auto rSenseWire = GetDescription().GetSenseWireDiameter() / 2;
        const auto rFieldWire = GetDescription<kSpectrometerCells>().GetFieldWireDiameter() / 2;
        const auto cellWidth = GetDescription<kSpectrometerReadoutLayer>().GetAverageCellWidth();

        auto material = Mother()->GetVolume()->GetLogicalVolume()->GetMaterial();

        int cellId = 0;
        fCellLayerIDAndPositionList.clear();
        for (int layerId = 0; layerId < Mother()->GetVolumeNum(); ++layerId) {
            const auto motherVolume = Mother()->GetVolume(layerId);
            const auto motherSolid = static_cast<const G4Tubs*>(motherVolume->GetLogicalVolume()->GetSolid());
            const auto halfLength = motherSolid->GetZHalfLength();
            const auto layerInnerRadius = motherSolid->GetInnerRadius();
            const auto layerOuterRadius = motherSolid->GetOuterRadius();
            const auto layerCenterRadius = (layerInnerRadius + layerOuterRadius) / 2;

            const int cellCount = 4 * std::lround(M_PI_2 / (2.0 * std::asin(0.5 * cellWidth / layerCenterRadius)));
            const auto cellAngle = 2 * M_PI / cellCount;
            const auto gapHalfAngle = rFieldWire / layerInnerRadius;
            auto solid = new G4Tubs(name, layerInnerRadius + rFieldWire, layerOuterRadius, halfLength, gapHalfAngle, cellAngle - 2.0 * gapHalfAngle);
            auto logic = new G4LogicalVolume(solid, material, name);
            for (int k = 0; k < cellCount; ++k) {
                auto cellPhi = k * cellAngle;
                auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(0.0, 0.0, 1.0), cellPhi), G4ThreeVector()), name, logic, motherVolume, true, cellId, fCheckOverlaps);
                fVolumes.emplace_back(physic);

                auto cellX = layerCenterRadius * std::cos(cellPhi);
                auto cellY = layerCenterRadius * std::sin(cellPhi);
                auto cellPosition = G4TwoVector(cellX, cellY);
                fCellLayerIDAndPositionList.emplace_back(layerId, cellPosition);
                ++cellId;
            }
        }
    }

private:
    std::vector<std::pair<G4int, G4TwoVector>> fCellLayerIDAndPositionList;
};
