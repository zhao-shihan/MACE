#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSecondTransportField/Collimator.hh"
#include "Geometry/Interface/EntityG4.hh"

class MACE::Geometry::Entity::Fast::Collimator final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::Collimator> {
    void ConstructSelf() override {
        auto name = GetDescription()->GetName();
        auto innerRadius = GetDescription()->GetInnerRadius();
        auto outerRadius = GetDescription()->GetOuterRadius();
        auto length = GetDescription()->GetLength();
        auto thickness = GetDescription()->GetThickness();
        auto zPosition = GetDescription()->GetZPosition();
        auto count = GetDescription()->GetCount();

        auto material = fgG4Nist->FindOrBuildMaterial("G4_Cu");

        for (size_t i = 0; i < count; ++i) {
            G4double radii = innerRadius + i * (outerRadius - innerRadius) / (count - 1);
            auto soild = new G4Tubs(name, radii, radii + thickness, 0.5 * length, 0, 2.0 * M_PI);
            auto logic = new G4LogicalVolume(soild, material, name);
            auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0.0, 0.0, zPosition), name, logic, MotherVolume(), false, 0, fgCheckOverlaps);
            fVolumes.emplace_back(physic);
        }
    }
};