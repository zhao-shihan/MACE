#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportSolenoid.hxx"
#include "Geometry/Description/DescendantsOfWorld/FirstTransportSolenoid.hxx"

using namespace MACE::Geometry::Entity::Fast;

void FirstTransportSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::FirstTransportSolenoid::Instance();
    auto name = description.GetName();
    auto innerRadius = description.GetInnerRaidus();
    auto outerRaidus = description.GetOuterRaidus();
    auto length = description.GetLength();
    auto upZPosition = description.GetUpZPosition();

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
            G4RotationMatrix(),
            G4ThreeVector(0, 0, upZPosition + length / 2)),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
