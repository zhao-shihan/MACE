#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/ThirdTransportSolenoid.hxx"
#include "Geometry/Description/DescendantsOfWorld/ThirdTransportSolenoid.hxx"

using namespace MACE::Geometry::Entity::Fast;

void ThirdTransportSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::ThirdTransportSolenoid::Instance();
    auto name = description.GetName();
    auto innerRadius = description.GetInnerRaidus();
    auto outerRaidus = description.GetOuterRaidus();
    auto length = description.GetLength();
    auto centerX = description.GetCenterX();
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
    Make<G4PVPlacement>(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(
                centerX,
                0,
                upZPosition + length / 2)),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
