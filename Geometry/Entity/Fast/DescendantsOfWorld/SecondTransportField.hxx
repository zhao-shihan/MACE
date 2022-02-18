#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/SecondTransportField.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::SecondTransportField final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SecondTransportField> {
    void ConstructSelf(bool checkOverlaps) override {
        auto name = GetDescription().GetName();
        auto length = GetDescription().GetLength();
        auto raidus = GetDescription().GetRadius();
        auto centerZ = GetDescription().GetCenterZ();
        auto upXPosition = GetDescription().GetUpXPosition();

        auto material = Mother()->GetVolume()->GetLogicalVolume()->GetMaterial();

        auto solid = new G4Tubs(name, 0.0, raidus, 0.5 * length, 0, 2.0 * M_PI);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(0.0, 1.0, 0.0), M_PI_2), G4ThreeVector(upXPosition + 0.5 * length, 0.0, centerZ)), name, logic, Mother()->GetVolume(), false, 0, checkOverlaps);
        fVolumes.emplace_back(physic);
    }
};