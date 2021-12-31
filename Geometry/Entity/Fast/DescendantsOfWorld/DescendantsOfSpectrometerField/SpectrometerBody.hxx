#pragma once

#include "G4Polycone.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::SpectrometerBody final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SpectrometerBody> {
    void ConstructSelf() override {
        auto name = GetDescription()->GetName();
        auto shellInnerThickness = GetDescription()->GetShellInnerThickness();
        auto shellSideThickness = GetDescription()->GetShellSideThickness();
        auto shellOuterThickness = GetDescription()->GetShellOuterThickness();
        auto gasInnerRadius = GetDescription()->GetGasInnerRadius();
        auto gasOuterRadius = GetDescription()->GetGasOuterRadius();
        auto gasInnerLength = GetDescription()->GetGasInnerLength();
        auto gasOuterLength = GetDescription()->GetGasOuterLength();

        auto shellMaterial = fgG4Nist->BuildMaterialWithNewDensity("CarbonFiber", "G4_C", 1.7_g_cm3);

        constexpr auto numZPlane = 4;
        const G4double zPlane[] = { -gasOuterLength / 2 - shellSideThickness, -gasInnerLength / 2 - shellSideThickness, gasInnerLength / 2 + shellSideThickness, gasOuterLength / 2 + shellSideThickness };
        const G4double rInner[] = { gasOuterRadius - shellInnerThickness, gasInnerRadius - shellInnerThickness, gasInnerRadius - shellInnerThickness, gasOuterRadius - shellInnerThickness };
        const G4double rOuter[] = { gasOuterRadius + shellOuterThickness, gasOuterRadius + shellOuterThickness, gasOuterRadius + shellOuterThickness, gasOuterRadius + shellOuterThickness };
        auto solid = new G4Polycone(name, 0, 2.0 * M_PI, numZPlane, zPlane, rInner, rOuter);
        auto logic = new G4LogicalVolume(solid, shellMaterial, name);
        auto physic = new G4PVPlacement(G4Transform3D(), name, logic, Mother()->GetVolume(), false, 0, fCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};