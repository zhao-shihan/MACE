#pragma once

#include "G4Box.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfCalorimeterField/OrbitalDetector.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::OrbitalDetector final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::OrbitalDetector> {
    void CreateSelf() override {
        auto name = GetDescription()->GetName();
        auto width = GetDescription()->GetWidth();
        auto thickness = GetDescription()->GetThickness();

        auto material = fgG4Nist->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4_g_cm3);

        auto solid = new G4Box(name, 0.5 * width, 0.5 * width, 0.5 * thickness);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, 0.5 * thickness), name, logic, MotherVolume(), false, 0, fgCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};