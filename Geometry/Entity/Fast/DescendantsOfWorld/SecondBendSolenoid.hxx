#pragma once

#include "G4Torus.hh"

#include "Geometry/Description/DescendantsOfWorld/SecondBendSolenoid.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::SecondBendSolenoid final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SecondBendSolenoid> {
    void ConstructSelf() override {
        auto name = GetDescription().GetName();
        auto innerRadius = GetDescription().GetInnerRaidus();
        auto outerRaidus = GetDescription().GetOuterRaidus();
        auto bendRadius = GetDescription().GetBendRadius();
        auto xPosition = GetDescription().GetXPosition();
        auto zPosition = GetDescription().GetZPosition();

        auto material = fgG4Nist->FindOrBuildMaterial("G4_Cu");

        auto solid = new G4Torus(name, innerRadius, outerRaidus, bendRadius, -M_PI_2, M_PI_2);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(G4RotationMatrix(G4ThreeVector(1.0, 0.0, 0.0), M_PI_2), G4ThreeVector(xPosition, 0.0, zPosition)), name, logic, Mother()->GetVolume(), false, 0, fCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};