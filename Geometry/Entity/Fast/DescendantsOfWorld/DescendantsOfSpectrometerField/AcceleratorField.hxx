#pragma once

#include "G4Box.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::AcceleratorField final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::AcceleratorField> {
    void ConstructSelf() override {
        auto name = GetDescription()->GetName();
        auto width = GetDescription()->GetWidth();
        auto upStreamLength = GetDescription()->GetUpStreamLength();
        auto downStreamLength = GetDescription()->GetDownStreamLength();

        auto material = Mother()->GetVolume()->GetLogicalVolume()->GetMaterial();

        auto solid = new G4Box(name, 0.5 * width, 0.5 * width, 0.5 * (upStreamLength + downStreamLength));
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0.5 * (downStreamLength - upStreamLength)), name, logic, Mother()->GetVolume(), false, 0, fCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};