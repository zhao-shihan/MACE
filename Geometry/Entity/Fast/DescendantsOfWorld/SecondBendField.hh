#pragma once

#include "G4Torus.hh"

#include "Geometry/Description/DescendantsOfWorld/SecondBendField.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::SecondBendField final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SecondBendField> {
    void ConstructSelf() override {
        auto name = GetDescription()->GetName();
        auto raidus = GetDescription()->GetRaidus();
        auto bendRadius = GetDescription()->GetBendRadius();
        auto xPosition = GetDescription()->GetXPosition();
        auto zPosition = GetDescription()->GetZPosition();

        auto material = MotherVolume()->GetLogicalVolume()->GetMaterial();

        auto solid = new G4Torus(name, 0, raidus, bendRadius, -M_PI_2, M_PI_2);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(1.0, 0.0, 0.0), M_PI_2), G4ThreeVector(xPosition, 0.0, zPosition)), name, logic, MotherVolume(), false, 0, fgCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};