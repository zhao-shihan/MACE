#include "Core/Geometry/Description/TransportLine.hxx"
#include "Core/Geometry/Entity/Fast/SecondBendField.hxx"

#include "G4PVPlacement.hh"
#include "G4Torus.hh"

namespace MACE::Core::Geometry::Entity::Fast {

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
        -M_PI_2,
        M_PI_2);
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
