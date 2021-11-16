#include "Geometry/Entity/World.hh"
#include "Geometry/Entity/Target.hh"

using namespace MACE::Geometry::Entity;
using namespace MACE::Geometry;

int main(int, char**) {
    auto world = std::make_unique<World>();
    auto target = std::make_unique<Target>();

    target->SetMother(world.get());

    world->CreateWholeFamily();

    gGeoManager->SetTopVolume(world->GetVolume());
    gGeoManager->CloseGeometry();
    gGeoManager->Draw();
    gGeoManager->Export("test.root");

    return 0;
}