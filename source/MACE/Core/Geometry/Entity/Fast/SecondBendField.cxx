#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Core/Geometry/Entity/Fast/SecondBendField.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4PVPlacement.hh"
#include "G4Torus.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void SecondBendField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "SecondBendField";
    const auto radius = description.GetFieldRadius();
    const auto bendRadius = description.GetSecondBendRadius();
    const auto transform = description.SecondBendTransform();

    auto solid = Make<G4Torus>(
        name,
        0,
        radius,
        bendRadius,
        -halfpi,
        halfpi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        transform,
        logic,
        name,
        Mother()->GetLogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
