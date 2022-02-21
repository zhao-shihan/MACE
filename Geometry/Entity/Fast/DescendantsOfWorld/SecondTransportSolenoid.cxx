#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondTransportSolenoid.hxx"
#include "Geometry/Description/DescendantsOfWorld/SecondTransportSolenoid.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SecondTransportSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SecondTransportSolenoid::Instance();
    auto name = description.GetName();
    auto length = description.GetLength();
    auto innerRadius = description.GetInnerRaidus();
    auto outerRaidus = description.GetOuterRaidus();
    auto centerZ = description.GetCenterZ();
    auto upXPosition = description.GetUpXPosition();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

    auto solid = Make<G4Tubs>(
        name,
        innerRadius,
        outerRaidus,
        length / 2,
        0,
        2 * M_PI);
    auto logic = Make<G4LogicalVolume>(
        solid,
        material,
        name);
    auto physics = Make<G4PVPlacement>(
        G4Transform3D(
            G4RotationMatrix(G4ThreeVector(0, 1, 0), M_PI_2),
            G4ThreeVector(upXPosition + length / 2, 0, centerZ)),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
