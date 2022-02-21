#include "G4Torus.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondBendSolenoid.hxx"
#include "Geometry/Description/DescendantsOfWorld/SecondBendSolenoid.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SecondBendSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SecondBendSolenoid::Instance();
    auto name = description.GetName();
    auto innerRadius = description.GetInnerRaidus();
    auto outerRaidus = description.GetOuterRaidus();
    auto bendRadius = description.GetBendRadius();
    auto xPosition = description.GetXPosition();
    auto zPosition = description.GetZPosition();

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
    auto physics = Make<G4PVPlacement>(
        G4Transform3D(
            G4RotationMatrix(G4ThreeVector(1, 0, 0), M_PI_2),
            G4ThreeVector(xPosition, 0, zPosition)),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
