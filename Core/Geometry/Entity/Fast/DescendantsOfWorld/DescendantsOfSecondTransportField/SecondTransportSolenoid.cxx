#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/SecondTransportSolenoid.hxx"
#include "Geometry/Description/DescendantsOfWorld/DescendantsOfSecondTransportField/SecondTransportSolenoid.hxx"

using namespace MACE::Geometry::Entity::Fast;

void SecondTransportSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SecondTransportSolenoid::Instance();
    auto name = description.GetName();
    auto length = description.GetLength();
    auto innerRadius = description.GetInnerRaidus();
    auto outerRaidus = description.GetOuterRaidus();

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
        G4Transform3D(),
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}
