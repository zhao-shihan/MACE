#pragma once

#include "G4Tubs.hh"
#include "G4UnionSolid.hh"

#include "Geometry/Description/DescendantsOfWorld/SpectrometerShield.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::SpectrometerShield final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::SpectrometerShield> {
    void CreateSelf() override {
        auto name = GetDescription()->GetName();
        auto innerRadius = GetDescription()->GetInnerRadius();
        auto innerLength = GetDescription()->GetInnerLength();
        auto windowRadius = GetDescription()->GetWindowRadius();
        auto thickness = GetDescription()->GetThickness();

        auto material = fgG4Nist->FindOrBuildMaterial("G4_Pb");

        auto body = new G4Tubs("_temp", innerRadius, innerRadius + thickness, 0.5 * innerLength, 0.0, 2 * M_PI);
        auto cap = new G4Tubs("_temp", windowRadius, innerRadius + thickness, 0.5 * thickness, 0.0, 2 * M_PI);
        auto temp = new G4UnionSolid("_temp", body, cap, G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.0, 0.0, -0.5 * innerLength - 0.5 * thickness)));
        auto solid = new G4UnionSolid(name, temp, cap, G4Transform3D(G4RotationMatrix(), G4ThreeVector(0.0, 0.0, 0.5 * innerLength + 0.5 * thickness)));
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(), name, logic, MotherVolume(), false, 0, fgCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};