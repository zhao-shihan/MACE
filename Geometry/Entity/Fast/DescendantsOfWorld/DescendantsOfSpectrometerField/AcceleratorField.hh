#pragma once

#include "G4Box.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::AcceleratorField final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::AcceleratorField> {
    void CreateSelf() override {
        auto name = GetDescription()->GetName();
        auto width = GetDescription()->GetWidth();
        auto upStreamLength = GetDescription()->GetUpStreamLength();
        auto downStreamLength = GetDescription()->GetDownStreamLength();

        auto material = MotherVolume()->GetLogicalVolume()->GetMaterial();

        auto solid = new G4Box(name, 0.5 * width, 0.5 * width, 0.5 * (upStreamLength + downStreamLength));
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0.5 * (downStreamLength - upStreamLength)), name, logic, MotherVolume(), false, 0, fgCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};