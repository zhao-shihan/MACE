#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::Calorimeter final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::Calorimeter> {
    void ConstructSelf(bool checkOverlaps) override {
        auto name = GetDescription().GetName();
        auto innerRadius = GetDescription().GetInnerRadius();
        auto outerRadius = GetDescription().GetOuterRadius();
        auto length = GetDescription().GetLength();

        auto material = fgG4Nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

        auto solid = new G4Tubs(name, innerRadius, outerRadius, 0.5 * length, 0, 2 * M_PI);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(G4Transform3D(), name, logic, Mother()->GetVolume(), false, 0, checkOverlaps);
        fVolumes.emplace_back(physic);
    }
};