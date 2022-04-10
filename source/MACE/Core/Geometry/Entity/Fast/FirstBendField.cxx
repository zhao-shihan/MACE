#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Core/Geometry/Entity/Fast/FirstBendField.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Torus.hh"

namespace MACE::Core::Geometry::Entity::Fast {

void FirstBendField::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::TransportLine::Instance();
    const auto name = "FirstBendField";
    const auto radius = description.GetFieldRadius();
    const auto bendRadius = description.GetFirstBendRadius();
    const auto transform = description.FirstBendTransform();

    auto solid = Make<G4Torus>(
        name,
        0,
        radius,
        bendRadius,
        M_PI_2,
        M_PI_2);
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
