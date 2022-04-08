#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Core/Geometry/Entity/Fast/ThirdTransportField.hxx"

#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Core::Geometry::Entity::Fast {

void ThirdTransportField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "ThirdTransportField";
    const auto length = description.GetThirdStraightLength();
    const auto radius = description.GetFieldRadius();
    const auto transform = description.ThirdStraightTransform();

    auto solid = Make<G4Tubs>(
        name,
        0,
        radius,
        length / 2,
        0,
        2 * M_PI);
    auto logic = Make<G4LogicalVolume>(
        solid,
        Mother()->GetMaterial(),
        name);
    Make<G4PVPlacement>(
        transform,
        name,
        logic,
        Mother()->GetPhysicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
