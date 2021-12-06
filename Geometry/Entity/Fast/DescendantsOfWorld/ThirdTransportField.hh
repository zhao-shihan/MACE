#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/ThirdTransportField.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::ThirdTransportField final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::ThirdTransportField> {
    void ConstructSelf() override {
        auto name = GetDescription()->GetName();
        auto raidus = GetDescription()->GetRadius();
        auto length = GetDescription()->GetLength();
        auto centerX = GetDescription()->GetCenterX();
        auto upZPosition = GetDescription()->GetUpZPosition();

        auto material = Mother()->GetVolume()->GetLogicalVolume()->GetMaterial();

        auto solid = new G4Tubs(name, 0.0, raidus, 0.5 * length, 0, 2.0 * M_PI);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(nullptr, G4ThreeVector(centerX, 0.0, upZPosition + 0.5 * length), name, logic, Mother()->GetVolume(), false, 0, fCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};