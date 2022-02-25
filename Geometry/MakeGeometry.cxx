#include "TGeoManager.h"

#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/Calorimeter.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfCalorimeterField/VertexDetector.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfFirstBendField/FirstBendSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfFirstTransportField/FirstTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondBendField/SecondBendSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/Collimator.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/SecondTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSecondTransportField/SelectorField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfAcceleratorField/Target.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/DescendantsOfSpectrometerReadoutLayer/SpectrometerCells.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/DescendantsOfSpectrometerBody/SpectrometerReadoutLayers.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/AcceleratorField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerBody.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfSpectrometerField/SpectrometerMagnet.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/DescendantsOfThirdTransportField/ThirdTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/CalorimeterField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/CalorimeterShield.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstBendField.hxx"
#include "Geometry/Entity/Fast/DescendantsOfWorld/FirstTransportField.hxx"
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
    auto firstBendSolenoid = std::make_shared<FirstBendSolenoid>();
    auto firstTransportSolenoid = std::make_shared<FirstTransportSolenoid>();
    auto secondBendSolenoid = std::make_shared<SecondBendSolenoid>();
    auto collimator = std::make_shared<Collimator>();
    auto secondTransportSolenoid = std::make_shared<SecondTransportSolenoid>();
    auto selectorField = std::make_shared<SelectorField>();
    auto target = std::make_shared<Target>();
    auto spectrometerCells = std::make_shared<SpectrometerCells>();
    auto spectrometerReadoutLayer = std::make_shared<SpectrometerReadoutLayers>();
    auto acceleratorField = std::make_shared<AcceleratorField>();
    auto spectrometerBody = std::make_shared<SpectrometerBody>();
    auto spectrometerMagnet = std::make_shared<SpectrometerMagnet>();
    auto thirdTransportSolenoid = std::make_shared<ThirdTransportSolenoid>();
    auto calorimeterField = std::make_shared<CalorimeterField>();
    auto calorimeterShield = std::make_shared<CalorimeterShield>();
    auto firstBendField = std::make_shared<FirstBendField>();
    auto firstTransportField = std::make_shared<FirstTransportField>();
    auto secondBendField = std::make_shared<SecondBendField>();
    auto secondTransportField = std::make_shared<SecondTransportField>();
    auto spectrometerField = std::make_shared<SpectrometerField>();
    auto spectrometerShield = std::make_shared<SpectrometerShield>();
    auto thirdTransportField = std::make_shared<ThirdTransportField>();
    auto world = std::make_shared<World>();

    calorimeterField->AddDaughter(calorimeter);
    calorimeterField->AddDaughter(vertexDetector);
    firstBendField->AddDaughter(firstBendSolenoid);
    firstTransportField->AddDaughter(firstTransportSolenoid);
    secondBendField->AddDaughter(secondBendSolenoid);
    secondTransportField->AddDaughter(collimator);
    secondTransportField->AddDaughter(secondTransportSolenoid);
    secondTransportField->AddDaughter(selectorField);
    spectrometerField->AddDaughter(acceleratorField);
    spectrometerField->AddDaughter(spectrometerBody);
    spectrometerField->AddDaughter(spectrometerMagnet);
    thirdTransportField->AddDaughter(thirdTransportSolenoid);
    acceleratorField->AddDaughter(target);
    spectrometerBody->AddDaughter(spectrometerReadoutLayer);
    spectrometerReadoutLayer->AddDaughter(spectrometerCells);
    world->AddDaughter(calorimeterField);
    world->AddDaughter(calorimeterShield);
    world->AddDaughter(firstBendField);
    world->AddDaughter(firstTransportField);
    world->AddDaughter(secondBendField);
    world->AddDaughter(secondTransportField);
    world->AddDaughter(spectrometerField);
    world->AddDaughter(spectrometerShield);
    world->AddDaughter(thirdTransportField);

    world->ConstructSelfAndDescendants(true);

    world->WriteSelfAndDesendentsToGDML("test.gdml");

    auto geoManager = std::make_unique<TGeoManager>("MACEGeom", "MACE Geometry");
    geoManager->Import("test.gdml");
    geoManager->Export("test.root");

    return EXIT_SUCCESS;
}
