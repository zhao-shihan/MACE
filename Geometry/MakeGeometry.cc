#include "Geometry/Entity/Fast/World.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/OrbitalDetector.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/Collimator.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerCells.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerShell.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/CalorimeterField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/OrbitalDetectorShield.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondBendField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondTransportField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerField.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerShield.hh"
#include "Geometry/Entity/Fast/DescendantsOfWorld/ThirdTransportField.hh"

using namespace MACE::Geometry::Entity::Fast;

int main(int, char**) {
    auto world = new World();
    auto target = new DescendantsOfWorld::DescendantsOfSpectrometerField::DescendantsOfAcceleratorField::Target();

    world->AddDaughter(target);

    world->CreateSelfAndDescendants();

    gGeoManager->SetTopVolume(world->GetVolume());
    gGeoManager->CloseGeometry();
    gGeoManager->Export("test.root");
    gGeoManager->Export("test.gdml");

    delete world;
    delete gGeoManager;

    return 0;
}