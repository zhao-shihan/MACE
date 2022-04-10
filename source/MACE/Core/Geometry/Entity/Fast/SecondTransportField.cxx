#include "MACE/Core/Geometry/Description/SpectrometerField.hxx"
#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Core/Geometry/Entity/Fast/SecondTransportField.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Core::Geometry::Entity::Fast {

void SecondTransportField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "SecondTransportField";
    const auto length = description.GetSecondStraightLength();
    const auto radius = description.GetFieldRadius();
    const auto transform = description.SecondStraightTransform();

    auto solid = Make<G4Tubs>(
        name,
        0,
        radius,
        length / 2,
        0,
        2 * M_PI);
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
