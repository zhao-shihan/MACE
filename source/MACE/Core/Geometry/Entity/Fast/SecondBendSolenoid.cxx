#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Core/Geometry/Entity/Fast/SecondBendSolenoid.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Torus.hh"

using MACE::Core::Geometry::Entity::Fast::SecondBendSolenoid;

void SecondBendSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "SecondBendSolenoid";
    const auto innerRadius = description.GetSolenoidInnerRadius();
    const auto outerRadius = description.GetSolenoidOuterRadius();
    const auto bendRadius = description.GetSecondBendRadius();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

    auto solid = Make<G4Torus>(
        name,
        innerRadius,
        outerRadius,
        bendRadius,
        -M_PI_2,
        M_PI_2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        material,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
