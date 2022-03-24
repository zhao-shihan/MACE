#include "Geometry/Entity/Fast/AcceleratorField.hxx"
#include "Geometry/Entity/Fast/Calorimeter.hxx"
#include "Geometry/Entity/Fast/CalorimeterField.hxx"
#include "Geometry/Entity/Fast/CalorimeterShield.hxx"
#include "Geometry/Entity/Fast/Collimator.hxx"
#include "Geometry/Entity/Fast/FirstBendField.hxx"
#include "Geometry/Entity/Fast/FirstBendSolenoid.hxx"
#include "Geometry/Entity/Fast/FirstTransportField.hxx"
#include "Geometry/Entity/Fast/FirstTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/SecondBendField.hxx"
#include "Geometry/Entity/Fast/SecondBendSolenoid.hxx"
#include "Geometry/Entity/Fast/SecondTransportField.hxx"
#include "Geometry/Entity/Fast/SecondTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/SelectorField.hxx"
#include "Geometry/Entity/Fast/SpectrometerBody.hxx"
#include "Geometry/Entity/Fast/SpectrometerCells.hxx"
#include "Geometry/Entity/Fast/SpectrometerField.hxx"
#include "Geometry/Entity/Fast/SpectrometerFieldWires.hxx"
#include "Geometry/Entity/Fast/SpectrometerMagnet.hxx"
#include "Geometry/Entity/Fast/SpectrometerReadoutLayers.hxx"
#include "Geometry/Entity/Fast/SpectrometerSenseWires.hxx"
#include "Geometry/Entity/Fast/SpectrometerSensitiveVolumes.hxx"
#include "Geometry/Entity/Fast/SpectrometerShield.hxx"
#include "Geometry/Entity/Fast/Target.hxx"
#include "Geometry/Entity/Fast/ThirdTransportField.hxx"
#include "Geometry/Entity/Fast/ThirdTransportSolenoid.hxx"
#include "Geometry/Entity/Fast/VertexDetector.hxx"
#include "Geometry/Entity/Fast/World.hxx"

#include "TGeoManager.h"

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
    auto spectrometerSenseWires = std::make_shared<SpectrometerSenseWires>();
    auto spectrometerFieldWires = std::make_shared<SpectrometerFieldWires>();
    auto spectrometerSensitiveVolumes = std::make_shared<SpectrometerSensitiveVolumes>();
    auto spectrometerCells = std::make_shared<SpectrometerCells>();
    auto spectrometerReadoutLayers = std::make_shared<SpectrometerReadoutLayers>();
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
    acceleratorField->AddDaughter(target);
    spectrometerSensitiveVolumes->AddDaughter(spectrometerSenseWires);
    spectrometerCells->AddDaughter(spectrometerFieldWires);
    spectrometerCells->AddDaughter(spectrometerSensitiveVolumes);
    spectrometerReadoutLayers->AddDaughter(spectrometerCells);
    spectrometerBody->AddDaughter(spectrometerReadoutLayers);
    spectrometerField->AddDaughter(acceleratorField);
    spectrometerField->AddDaughter(spectrometerBody);
    spectrometerField->AddDaughter(spectrometerMagnet);
    thirdTransportField->AddDaughter(thirdTransportSolenoid);
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
