#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hh"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::SpectrometerCells final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SpectrometerCells> {
    void ConstructSelf() override {
        const auto name = GetDescription()->GetName();
        // const auto rSenseWire = GetDescription()->GetSenseWireDiameter() / 2;
        const auto rFieldWire = GetDescription()->GetFieldWireDiameter() / 2;
        const auto cellWidth = GetDescription()->GetAverageCellWidth();

        auto material = Mother()->GetVolume()->GetLogicalVolume()->GetMaterial();

        int cellId = 0;
        for (int i = 0; i < Mother()->GetVolumeNum(); ++i) {
            const auto motherVolume = Mother()->GetVolume(i);
            const auto motherSolid = static_cast<const G4Tubs*>(motherVolume->GetLogicalVolume()->GetSolid());
            const auto halfLength = motherSolid->GetZHalfLength();
            const auto layerInnerRadius = motherSolid->GetInnerRadius();
            const auto layerOuterRadius = motherSolid->GetOuterRadius();
            const auto layerCenterRadius = (layerInnerRadius + layerOuterRadius) / 2.0;

            const int cellCount = round(2.0 * M_PI / (2.0 * asin(0.5 * cellWidth / layerCenterRadius)));
            const auto cellAngle = 2.0 * M_PI / cellCount;
            const auto gapHalfAngle = rFieldWire / layerInnerRadius;
            auto solid = new G4Tubs(name, layerInnerRadius + rFieldWire, layerOuterRadius, halfLength, gapHalfAngle, cellAngle - 2.0 * gapHalfAngle);
            auto logic = new G4LogicalVolume(solid, material, name);
            for (int j = 0; j < cellCount; ++j) {
                auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(0.0, 0.0, 1.0), j * cellAngle), G4ThreeVector()), name, logic, motherVolume, true, cellId, fCheckOverlaps);
                fVolumes.emplace_back(physic);
                ++cellId;
            }
        }
    }
};