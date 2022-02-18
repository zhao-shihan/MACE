#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::SelectorField final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SelectorField> {
    void ConstructSelf(bool checkOverlaps) override {
        auto name = GetDescription().GetName();
        auto raidus = GetDescription().GetRaidus();
        auto length = GetDescription().GetLength();
        auto zPosition = GetDescription().GetZPosition();

        auto material = Mother()->GetVolume()->GetLogicalVolume()->GetMaterial();

        auto solid = new G4Tubs(name, 0.0, raidus, 0.5 * length, 0, 2 * M_PI);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, zPosition), name, logic, Mother()->GetVolume(), false, 0, checkOverlaps);
        fVolumes.emplace_back(physic);
    }
};