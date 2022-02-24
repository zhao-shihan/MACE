#include "G4Torus.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendSolenoid.hxx"
#include "Geometry/Description/DescendantsOfWorld/FirstBendSolenoid.hxx"

using namespace MACE::Geometry::Entity::Fast;

void FirstBendSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::FirstBendSolenoid::Instance();
    const auto name = description.GetName();
    const auto innerRadius = description.GetInnerRaidus();
    const auto outerRaidus = description.GetOuterRaidus();
    const auto bendRadius = description.GetBendRadius();
    const auto xPosition = description.GetXPosition();
    const auto zPosition = description.GetZPosition();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

    auto solid = Make<G4Torus>(
        name,
        innerRadius,
        outerRaidus,
        bendRadius,
        M_PI_2,
        M_PI_2);
    auto logic = Make<G4LogicalVolume>(
        solid,
        material,
        name);
    Make<G4PVPlacement>(
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
