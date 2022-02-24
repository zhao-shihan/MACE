#include "G4Box.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

#include "Geometry/Entity/Fast/World.hxx"
#include "Geometry/Description/World.hxx"

using namespace MACE::Geometry::Entity::Fast;

void World::ConstructSelf(G4bool checkOverlaps) {
    const auto& description = Description::World::Instance();
    auto name = description.GetName();
    auto halfX = description.GetHalfXExtent();
    auto halfY = description.GetHalfYExtent();
    auto halfZ = description.GetHalfZExtent();

    auto material = G4NistManager::Instance()->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3, 293.145_K);

    auto solid = Make<G4Box>(
        name,
        halfX,
        halfY,
        halfZ);
    auto logic = Make<G4LogicalVolume>(
        solid,
        material,
        name);
    Make<G4PVPlacement>(
        G4Transform3D(),
        name,
        logic,
        nullptr,
        false,
        0,
        checkOverlaps);
}
