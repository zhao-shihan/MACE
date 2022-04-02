#include "Core/Geometry/Description/TransportLine.hxx"
#include "Core/Geometry/Entity/Fast/FirstTransportSolenoid.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::FirstTransportSolenoid;

void FirstTransportSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "FirstTransportSolenoid";
    const auto innerRadius = description.GetSolenoidInnerRadius();
    const auto outerRadius = description.GetSolenoidOuterRadius();
    const auto length = description.GetFirstStraightLength();

    auto material = G4NistManager::Instance()->FindOrBuildMaterial("G4_Cu");

    auto solid = Make<G4Tubs>(
        name,
        innerRadius,
        outerRadius,
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
