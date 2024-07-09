#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/World.h++"

#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

namespace MACE::Detector::Definition {

auto World::Construct(G4bool checkOverlaps) -> void {
    const auto& world{Description::World::Instance()};

    const auto solid{Make<G4Box>(
        world.Name(),
        world.HalfXExtent(),
        world.HalfYExtent(),
        world.HalfZExtent())};
    const auto logic{Make<G4LogicalVolume>(
        solid,
        G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR"),
        world.Name())};
    Make<G4PVPlacement>(
        G4Transform3D{},
        logic,
        world.Name(),
        nullptr,
        false,
        0,
        checkOverlaps);
}

} // namespace MACE::Detector::Definition
