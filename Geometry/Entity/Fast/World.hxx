#pragma once

#include "G4Box.hh"

#include "Geometry/Description/World.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::World final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::World> {
    void ConstructSelf() override {
        auto name = GetDescription()->GetName();
        auto halfX = GetDescription()->GetHalfXExtent();
        auto halfY = GetDescription()->GetHalfYExtent();
        auto halfZ = GetDescription()->GetHalfZExtent();

        auto material = fgG4Nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3, 293.145_K);

        auto solid = new G4Box(name, halfX, halfY, halfZ);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(), name, logic, nullptr, false, 0, fCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};