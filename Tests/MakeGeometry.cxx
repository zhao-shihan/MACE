#include "Core/Geometry/Entity/Fast/AcceleratorField.hxx"
#include "Core/Geometry/Entity/Fast/Calorimeter.hxx"
#include "Core/Geometry/Entity/Fast/CalorimeterField.hxx"
#include "Core/Geometry/Entity/Fast/CalorimeterShield.hxx"
#include "Core/Geometry/Entity/Fast/Collimator.hxx"
#include "Core/Geometry/Entity/Fast/FirstBendField.hxx"
#include "Core/Geometry/Entity/Fast/FirstBendSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/FirstTransportField.hxx"
#include "Core/Geometry/Entity/Fast/FirstTransportSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/SecondBendField.hxx"
#include "Core/Geometry/Entity/Fast/SecondBendSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/SecondTransportField.hxx"
#include "Core/Geometry/Entity/Fast/SecondTransportSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/SelectorField.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerBody.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerCells.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerField.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerFieldWires.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerMagnet.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerReadoutLayers.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerSenseWires.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerSensitiveVolumes.hxx"
#include "Core/Geometry/Entity/Fast/SpectrometerShield.hxx"
#include "Core/Geometry/Entity/Fast/Target.hxx"
#include "Core/Geometry/Entity/Fast/ThirdTransportField.hxx"
#include "Core/Geometry/Entity/Fast/ThirdTransportSolenoid.hxx"
#include "Core/Geometry/Entity/Fast/VertexDetector.hxx"
#include "Core/Geometry/Entity/Fast/World.hxx"

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
