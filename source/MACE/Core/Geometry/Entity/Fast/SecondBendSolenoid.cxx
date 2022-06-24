#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Core/Geometry/Entity/Fast/SecondBendSolenoid.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Torus.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void SecondBendSolenoid::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "SecondBendSolenoid";
    const auto innerRadius = description.GetSolenoidInnerRadius();
    const auto outerRadius = description.GetSolenoidOuterRadius();
    const auto bendRadius = description.GetSecondBendRadius();

    auto solid = Make<G4Torus>(
        name,
        innerRadius,
        outerRadius,
        bendRadius,
        -halfpi,
        halfpi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother()->GetLogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
