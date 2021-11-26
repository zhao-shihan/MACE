#include "TGeoManager.h"

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
#include "Geometry/Entity/Fast/World.hh"

using namespace MACE::Geometry::Entity::Fast;

int main(int, char**) {
    auto calorimeter = new Calorimeter();
    auto orbitalDetector = new OrbitalDetector();
    auto collimator = new Collimator();
    auto selectorField = new SelectorField();
    auto target = new Target();
    auto acceleratorField = new AcceleratorField();
    auto spectrometerCells = new SpectrometerCells();
    auto spectrometerShell = new SpectrometerShell();
    auto calorimeterField = new CalorimeterField();
    auto firstBendField = new FirstBendField();
    auto firstTransportField = new FirstTransportField();
    auto orbitalDetectorShield = new OrbitalDetectorShield();
    auto secondBendField = new SecondBendField();
    auto secondTransportField = new SecondTransportField();
    auto spectrometerField = new SpectrometerField();
    auto spectrometerShield = new SpectrometerShield();
    auto thirdTransportField = new ThirdTransportField();
    auto world = new World();

    world->AddDaughter(calorimeterField);
    world->AddDaughter(firstBendField);
    world->AddDaughter(firstTransportField);
    world->AddDaughter(orbitalDetectorShield);
    world->AddDaughter(secondBendField);
    world->AddDaughter(secondTransportField);
    world->AddDaughter(spectrometerField);
    world->AddDaughter(spectrometerShield);
    world->AddDaughter(thirdTransportField);
    calorimeterField->AddDaughter(calorimeter);
    calorimeterField->AddDaughter(orbitalDetector);
    secondTransportField->AddDaughter(collimator);
    secondTransportField->AddDaughter(selectorField);
    spectrometerField->AddDaughter(acceleratorField);
    spectrometerField->AddDaughter(spectrometerCells);
    spectrometerField->AddDaughter(spectrometerShell);
    acceleratorField->AddDaughter(target);

    world->CreateSelfAndDescendants();

    world->WriteSelfAndDesendentsToGDML("test.gdml");

    new TGeoManager("MACEGeom", "MACE Geometry");
    gGeoManager->Import("test.gdml");
    gGeoManager->Export("test.root");

    delete world;
    delete gGeoManager;

    return 0;
}