#include "MACE/Core/Geometry/Description/SpectrometerMagnet.hxx"
#include "MACE/Core/Geometry/Entity/Fast/SpectrometerMagnet.hxx"

#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

using MACE::Core::Geometry::Entity::Fast::SpectrometerMagnet;

void SpectrometerMagnet::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::SpectrometerMagnet::Instance();
    const auto name = description.GetName();
    const auto innerRadius = description.GetInnerRadius();
    const auto outerRadius = description.GetOuterRadius();
    const auto length = description.GetLength();

    auto solid = Make<G4Tubs>(
        name,
        innerRadius,
        outerRadius,
        length / 2,
        0,
        2 * M_PI);
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
