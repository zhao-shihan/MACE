#include "MACE/Geometry/Description/SpectrometerMagnet.hxx"
#include "MACE/Geometry/Entity/Fast/SpectrometerMagnet.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

namespace MACE::Geometry::Entity::Fast {

using namespace MACE::PhysicalConstant;

void SpectrometerMagnet::Construct(G4bool checkOverlaps) {
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
        Mother().LogicalVolume().get(),
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Geometry::Entity::Fast
