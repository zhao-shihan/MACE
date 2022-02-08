#include "TGeoManager.h"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/VertexDetector.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/Collimator.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayer.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/CalorimeterField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/VertexDetectorShield.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondBendField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SecondTransportField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/SpectrometerShield.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/ThirdTransportField.hxx"
#include "Geometry/Entity/Fast/World.hxx"

using namespace MACE::Geometry::Entity::Fast;

int main(int, char**) {
    auto calorimeter = new Calorimeter();
    auto vertexDetector = new VertexDetector();
    auto collimator = new Collimator();
    auto selectorField = new SelectorField();
    auto target = new Target();
    auto spectrometerCells = new SpectrometerCells();
    auto spectrometerReadoutLayer = new SpectrometerReadoutLayer();
    auto acceleratorField = new AcceleratorField();
    auto spectrometerBody = new SpectrometerBody();
    auto calorimeterField = new CalorimeterField();
    auto firstBendField = new FirstBendField();
    auto firstTransportField = new FirstTransportField();
    auto vertexDetectorShield = new VertexDetectorShield();
    auto secondBendField = new SecondBendField();
    auto secondTransportField = new SecondTransportField();
    auto spectrometerField = new SpectrometerField();
    auto spectrometerShield = new SpectrometerShield();
    auto thirdTransportField = new ThirdTransportField();
    auto world = new World();

    world->AddDaughter(calorimeterField);
    world->AddDaughter(firstBendField);
    world->AddDaughter(firstTransportField);
    world->AddDaughter(vertexDetectorShield);
    world->AddDaughter(secondBendField);
    world->AddDaughter(secondTransportField);
    world->AddDaughter(spectrometerField);
    world->AddDaughter(spectrometerShield);
    world->AddDaughter(thirdTransportField);
    calorimeterField->AddDaughter(calorimeter);
    calorimeterField->AddDaughter(vertexDetector);
    secondTransportField->AddDaughter(collimator);
    secondTransportField->AddDaughter(selectorField);
    spectrometerField->AddDaughter(acceleratorField);
    spectrometerField->AddDaughter(spectrometerBody);
    acceleratorField->AddDaughter(target);
    spectrometerBody->AddDaughter(spectrometerReadoutLayer);
    spectrometerReadoutLayer->AddDaughter(spectrometerCells);

    world->ConstructSelfAndDescendants();

    world->WriteSelfAndDesendentsToGDML("test.gdml");

    new TGeoManager("MACEGeom", "MACE Geometry");
    gGeoManager->Import("test.gdml");
    gGeoManager->Export("test.root");

    delete world;
    delete gGeoManager;

    return 0;
}