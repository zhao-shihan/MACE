#include "Geometry/EntityROOT/World.hh"
#include "Geometry/EntityROOT/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hh"

using namespace MACE::Geometry::EntityROOT;

int main(int, char**) {
    auto world = new World();
    auto target = new DescendantsOfWorld::DescendantsOfSpectrometerField::DescendantsOfAcceleratorField::Target();

    world->AddDaughter(target);

    world->CreateSelfAndDescendants();

    gGeoManager->SetTopVolume(world->GetVolume());
    gGeoManager->CloseGeometry();
    gGeoManager->Draw();
    gGeoManager->Export("test.root");

    delete world;
    delete gGeoManager;

    return 0;
}