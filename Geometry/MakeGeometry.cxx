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
    auto calorimeter = std::make_shared<Calorimeter>();
    auto vertexDetector = std::make_shared<VertexDetector>();
    auto collimator = std::make_shared<Collimator>();
    auto selectorField = std::make_shared<SelectorField>();
    auto target = std::make_shared<Target>();
    auto spectrometerCells = std::make_shared<SpectrometerCells>();
    auto spectrometerReadoutLayer = std::make_shared<SpectrometerReadoutLayer>();
    auto acceleratorField = std::make_shared<AcceleratorField>();
    auto spectrometerBody = std::make_shared<SpectrometerBody>();
    auto calorimeterField = std::make_shared<CalorimeterField>();
    auto firstBendField = std::make_shared<FirstBendField>();
    auto firstTransportField = std::make_shared<FirstTransportField>();
    auto vertexDetectorShield = std::make_shared<VertexDetectorShield>();
    auto secondBendField = std::make_shared<SecondBendField>();
    auto secondTransportField = std::make_shared<SecondTransportField>();
    auto spectrometerField = std::make_shared<SpectrometerField>();
    auto spectrometerShield = std::make_shared<SpectrometerShield>();
    auto thirdTransportField = std::make_shared<ThirdTransportField>();
    auto world = std::make_shared<World>();

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

    world->ConstructSelfAndDescendants(true);

    world->WriteSelfAndDesendentsToGDML("test.gdml");

    new TGeoManager("MACEGeom", "MACE Geometry");
    gGeoManager->Import("test.gdml");
    gGeoManager->Export("test.root");
    delete gGeoManager;

    return EXIT_SUCCESS;
}
