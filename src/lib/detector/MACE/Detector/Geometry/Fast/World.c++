#include "MACE/Detector/Description/World.h++"
#include "MACE/Detector/Geometry/Fast/World.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace MACE::Detector::Geometry::Fast {

using namespace LiteralUnit::Density;
using namespace LiteralUnit::Temperature;

void World::Construct(G4bool checkOverlaps) {
    const auto& description = Description::World::Instance();
    auto name = description.Name();
    auto halfX = description.HalfXExtent();
    auto halfY = description.HalfYExtent();
    auto halfZ = description.HalfZExtent();

    auto solid = Make<G4Box>(
        name,
        halfX,
        halfY,
        halfZ);
    auto logic = Make<G4LogicalVolume>(
        solid,
        nullptr,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        logic,
        name,
        nullptr,
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Geometry::Fast::World
