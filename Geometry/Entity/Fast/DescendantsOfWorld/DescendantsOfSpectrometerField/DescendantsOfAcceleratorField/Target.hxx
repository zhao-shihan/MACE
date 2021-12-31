#pragma once

#include "G4Box.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::Target final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::Target> {
    void ConstructSelf() override {
        auto name = GetDescription()->GetName();
        auto width = GetDescription()->GetWidth();
        auto thickness = GetDescription()->GetThickness();
        auto downZ = GetDescription()->GetDownZPosition();

        auto material = fgG4Nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30_mg_cm3);

        auto solid = new G4Box(name, 0.5 * width, 0.5 * width, 0.5 * thickness);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, downZ - 0.5 * thickness), name, logic, Mother()->GetVolume(), false, 0, fCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};