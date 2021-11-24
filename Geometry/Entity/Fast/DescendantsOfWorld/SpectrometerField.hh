#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/SpectrometerField.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::SpectrometerField final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SpectrometerField> {
    void CreateSelf() override {
        auto name = GetDescription()->GetName();
        auto length = GetDescription()->GetLength();
        auto raidus = GetDescription()->GetRadius();

        auto material = MotherVolume()->GetLogicalVolume()->GetMaterial();

        auto solid = new G4Tubs(name, 0.0, raidus, 0.5 * length, 0.0, 2.0 * M_PI);
        auto logic = new G4LogicalVolume(solid, material, solid->GetName());
        auto physic = new G4PVPlacement(G4Transform3D(), solid->GetName(), logic, MotherVolume(), false, 0, fgCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};