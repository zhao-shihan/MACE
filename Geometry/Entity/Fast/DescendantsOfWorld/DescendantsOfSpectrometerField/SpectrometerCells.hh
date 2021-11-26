#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerCells.hh"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerShell.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::SpectrometerCells final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SpectrometerCells, MACE::Geometry::Description::SpectrometerShell> {
    enum { kSpectrometerCells, kSpectrometerShell };
    void ConstructSelf() override {
        auto name = GetDescription<kSpectrometerCells>()->GetName();
        auto avgWidth = GetDescription<kSpectrometerCells>()->GetAverageCellWidth();
        auto innerRadius = GetDescription<kSpectrometerShell>()->GetInnerRadius();
        auto outerRadius = GetDescription<kSpectrometerShell>()->GetOuterRadius();
        auto innerLength = GetDescription<kSpectrometerShell>()->GetInnerLength();
        auto outerLength = GetDescription<kSpectrometerShell>()->GetOuterLength();

        auto material = fgG4Nist->FindOrBuildMaterial("G4_He");

        auto sideSlope = 0.5 * (outerLength - innerLength) / (outerRadius - innerRadius);
        int layerCount = floor((outerRadius - innerRadius) / avgWidth);
        for (int i = 0; i < layerCount; ++i) {
            auto halfLength = 0.5 * innerLength + i * avgWidth * sideSlope;
            auto layerCenterRadius = innerRadius + (i + 0.5) * avgWidth;
            int cellCount = round(2.0 * M_PI / (2.0 * asin(0.5 * avgWidth / layerCenterRadius)));
            auto cellAngle = 2.0 * M_PI / cellCount;
            auto solid = new G4Tubs(name, layerCenterRadius - 0.5 * avgWidth, layerCenterRadius + 0.5 * avgWidth, halfLength, 0.0, cellAngle);
            auto logic = new G4LogicalVolume(solid, material, name);
            for (int j = 0; j < cellCount; ++j) {
                auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(0.0, 0.0, 1.0), j * cellAngle), G4ThreeVector()), name, logic, MotherVolume(), true, j, fgCheckOverlaps);
                fVolumes.emplace_back(physic);
            }
        }
    }
};