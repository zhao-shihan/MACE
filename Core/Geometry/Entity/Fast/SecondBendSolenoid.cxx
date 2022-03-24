#include "Geometry/Description/SecondBendSolenoid.hxx"
#include "Geometry/Entity/Fast/SecondBendSolenoid.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Torus.hh"

using MACE::Geometry::Entity::Fast::SecondBendSolenoid;

void SecondBendSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SecondBendSolenoid::Instance();
    auto name = description.GetName();
    auto innerRadius = description.GetInnerRaidus();
    auto outerRaidus = description.GetOuterRaidus();
    auto bendRadius = description.GetBendRadius();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

    auto solid = Make<G4Torus>(
        name,
        innerRadius,
        outerRaidus,
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
