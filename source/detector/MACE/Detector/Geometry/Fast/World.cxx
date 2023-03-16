#include "MACE/Detector/Description/World.hxx"
#include "MACE/Detector/Geometry/Fast/World.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

using MACE::Detector::Geometry::Fast::World;
using namespace MACE::LiteralUnit::Density;
using namespace MACE::LiteralUnit::Temperature;

void World::Construct(G4bool checkOverlaps) {
    const auto& description = Description::World::Instance();
    auto name = description.GetName();
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
