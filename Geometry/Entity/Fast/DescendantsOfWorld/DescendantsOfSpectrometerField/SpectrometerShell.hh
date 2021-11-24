#pragma once

#include "G4Polycone.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerShell.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::SpectrometerShell final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SpectrometerShell> {
    void CreateSelf() override {
        auto name = GetDescription()->GetName();
        auto innerRadius = GetDescription()->GetInnerRadius();
        auto outerRadius = GetDescription()->GetOuterRadius();
        auto innerLength = GetDescription()->GetInnerLength();
        auto outerLength = GetDescription()->GetOuterLength();
        auto innerThickness = GetDescription()->GetInnerThickness();
        auto sideThickness = GetDescription()->GetSideThickness();
        auto outerThickness = GetDescription()->GetOuterThickness();

        auto material = fgG4Nist->BuildMaterialWithNewDensity("CarbonFiber", "G4_C", 1.7_g_cm3);

        const G4double zPlane[] = { -outerLength / 2 - sideThickness, -innerLength / 2 - sideThickness, innerLength / 2 + sideThickness, outerLength / 2 + sideThickness };
        const G4double rInner[] = { outerRadius - innerThickness, innerRadius - innerThickness, innerRadius - innerThickness, outerRadius - innerThickness };
        const G4double rOuter[] = { outerRadius + outerThickness, outerRadius + outerThickness, outerRadius + outerThickness, outerRadius + outerThickness };
        auto solid = new G4Polycone(name, 0, 2.0 * M_PI, 4, zPlane, rInner, rOuter);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(), name, logic, MotherVolume(), false, 0, fgCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};