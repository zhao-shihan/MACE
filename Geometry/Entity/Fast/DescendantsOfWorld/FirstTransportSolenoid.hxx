#pragma once

#include "G4Tubs.hh"

#include "Geometry/Description/DescendantsOfWorld/FirstTransportSolenoid.hxx"
#include "Geometry/Interface/EntityG4.hxx"

class MACE::Geometry::Entity::Fast::FirstTransportSolenoid final :
    public MACE::Geometry::Interface::EntityG4<MACE::Geometry::Description::FirstTransportSolenoid> {
    void ConstructSelf() override {
        auto name = GetDescription().GetName();
        auto innerRadius = GetDescription().GetInnerRaidus();
        auto outerRaidus = GetDescription().GetOuterRaidus();
        auto length = GetDescription().GetLength();
        auto upZPosition = GetDescription().GetUpZPosition();

        auto material = fgG4Nist->FindOrBuildMaterial("G4_Cu");

        auto solid = new G4Tubs(name, innerRadius, outerRaidus, 0.5 * length, 0, 2 * M_PI);
        auto logic = new G4LogicalVolume(solid, material, name);
        auto physic = new G4PVPlacement(nullptr, G4ThreeVector(0, 0, upZPosition + 0.5 * length), name, logic, Mother()->GetVolume(), false, 0, fCheckOverlaps);
        fVolumes.emplace_back(physic);
    }
};