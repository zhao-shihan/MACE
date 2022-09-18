#include "MACE/Core/Geometry/Description/SpectrometerMagnet.hxx"
#include "MACE/Core/Geometry/Entity/Fast/SpectrometerMagnet.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Core::Geometry::Entity::Fast {

using namespace MACE::Utility::PhysicalConstant;

void SpectrometerMagnet::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerMagnet::Instance();
    const auto name = description.GetName();
    const auto innerRadius = description.InnerRadius();
    const auto outerRadius = description.OuterRadius();
    const auto length = description.Length();

    auto solid = Make<G4Tubs>(
        name,
        innerRadius,
        outerRadius,
        length / 2,
        0,
        twopi);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        Mother()->LogicalVolume(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Core::Geometry::Entity::Fast
