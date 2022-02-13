#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/CalorimeterField.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::CalorimeterField final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::CalorimeterField> {
    void ConstructSelf() override {
        auto name = GetDescription().GetName();
        auto radius = GetDescription().GetRadius();
        auto length = GetDescription().GetLength();
        auto centerX = GetDescription().GetCenterX();
        auto upZPosition = GetDescription().GetUpZPosition();

        auto material = Mother()->GetVolume()->GetLogicalVolume()->GetMaterial();

        auto solid = new G4Tubs(name, 0.0, radius, 0.5 * length, 0.0, 2.0 * M_PI);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(nullptr, G4ThreeVector(centerX, 0.0, upZPosition + 0.5 * length), name, logic, Mother()->GetVolume(), false, 0, fCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};