#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerReadoutLayer final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SpectrometerReadoutLayer, MACE::Geometry::Description::SpectrometerBody> {
    enum { kSpectrometerReadoutLayer, kSpectrometerBody };
    void ConstructSelf() override {
        const auto name = GetDescription<kSpectrometerReadoutLayer>()->GetName();
        const auto layerThickness = GetDescription<kSpectrometerReadoutLayer>()->GetLayerThickness();
        const auto gasInnerRadius = GetDescription<kSpectrometerBody>()->GetGasInnerRadius();
        const auto gasOuterRadius = GetDescription<kSpectrometerBody>()->GetGasOuterRadius();
        const auto gasInnerLength = GetDescription<kSpectrometerBody>()->GetGasInnerLength();
        const auto gasOuterLength = GetDescription<kSpectrometerBody>()->GetGasOuterLength();

        auto material = fgG4Nist->FindOrBuildMaterial("G4_He");

        auto sideSlope = 0.5 * (gasOuterLength - gasInnerLength) / (gasOuterRadius - gasInnerRadius);
        const int layerCount = floor((gasOuterRadius - gasInnerRadius) / layerThickness);
        for (int i = 0; i < layerCount; ++i) {
            const auto halfLength = 0.5 * gasInnerLength + i * layerThickness * sideSlope;
            const auto layerCenterRadius = gasInnerRadius + (i + 0.5) * layerThickness;
            auto solid = new G4Tubs(name, layerCenterRadius - 0.5 * layerThickness, layerCenterRadius + 0.5 * layerThickness, halfLength, 0.0, 2.0 * M_PI);
            auto logic = new G4LogicalVolume(solid, material, name);
            auto physics = new G4PVPlacement(G4Transform3D(), name, logic, Mother()->GetVolume(), true, i, fCheckOverlaps);
            fVolumes.emplace_back(physics);
        }
    }
};