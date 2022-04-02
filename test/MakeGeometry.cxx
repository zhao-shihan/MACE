#include "Core/Geometry/Entity/Fast/All.hxx"

#include "TGeoManager.h"

using namespace MACE::Core::Geometry::Entity::Fast;

int main(int, char**) {
    // Construct entity objects
    auto fAcceleratorField = std::make_shared<AcceleratorField>();
    auto fCalorimeter = std::make_shared<Calorimeter>();
    auto fCalorimeterField = std::make_shared<CalorimeterField>();
    auto fCalorimeterShield = std::make_shared<CalorimeterShield>();
    auto fCDCBody = std::make_shared<CDCBody>();
    auto fCDCCell = std::make_shared<CDCCell>();
    auto fCDCFieldWire = std::make_shared<CDCFieldWire>();
    auto fCDCLayer = std::make_shared<CDCLayer>();
    auto fCDCSenseWire = std::make_shared<CDCSenseWire>();
    auto fCDCSensitiveVolume = std::make_shared<CDCSensitiveVolume>();
    auto fCollimator = std::make_shared<Collimator>();
    auto fFirstBendField = std::make_shared<FirstBendField>();
    auto fFirstBendSolenoid = std::make_shared<FirstBendSolenoid>();
    auto fFirstTransportField = std::make_shared<FirstTransportField>();
    auto fFirstTransportSolenoid = std::make_shared<FirstTransportSolenoid>();
    auto fSecondBendField = std::make_shared<SecondBendField>();
    auto fSecondBendSolenoid = std::make_shared<SecondBendSolenoid>();
    auto fSecondTransportField = std::make_shared<SecondTransportField>();
    auto fSecondTransportSolenoid = std::make_shared<SecondTransportSolenoid>();
    auto fSelectorField = std::make_shared<SelectorField>();
    auto fSpectrometerField = std::make_shared<SpectrometerField>();
    auto fSpectrometerMagnet = std::make_shared<SpectrometerMagnet>();
    auto fSpectrometerShield = std::make_shared<SpectrometerShield>();
    auto fTarget = std::make_shared<Target>();
    auto fThirdTransportField = std::make_shared<ThirdTransportField>();
    auto fThirdTransportSolenoid = std::make_shared<ThirdTransportSolenoid>();
    auto fVertexDetector = std::make_shared<VertexDetector>();
    auto fWorld = std::make_shared<World>();

    // Construct hierarchy
    fCalorimeterField->AddDaughter(fCalorimeter);
    fCalorimeterField->AddDaughter(fVertexDetector);
    fFirstBendField->AddDaughter(fFirstBendSolenoid);
    fFirstTransportField->AddDaughter(fFirstTransportSolenoid);
    fSecondBendField->AddDaughter(fSecondBendSolenoid);
    fSecondTransportField->AddDaughter(fCollimator);
    fSecondTransportField->AddDaughter(fSecondTransportSolenoid);
    fSecondTransportField->AddDaughter(fSelectorField);
    fAcceleratorField->AddDaughter(fTarget);
    fCDCSensitiveVolume->AddDaughter(fCDCSenseWire);
    fCDCCell->AddDaughter(fCDCFieldWire);
    fCDCCell->AddDaughter(fCDCSensitiveVolume);
    fCDCLayer->AddDaughter(fCDCCell);
    fCDCBody->AddDaughter(fCDCLayer);
    fSpectrometerField->AddDaughter(fAcceleratorField);
    fSpectrometerField->AddDaughter(fCDCBody);
    fSpectrometerField->AddDaughter(fSpectrometerMagnet);
    fThirdTransportField->AddDaughter(fThirdTransportSolenoid);
    fWorld->AddDaughter(fCalorimeterField);
    fWorld->AddDaughter(fCalorimeterShield);
    fWorld->AddDaughter(fFirstBendField);
    fWorld->AddDaughter(fFirstTransportField);
    fWorld->AddDaughter(fSecondBendField);
    fWorld->AddDaughter(fSecondTransportField);
    fWorld->AddDaughter(fSpectrometerField);
    fWorld->AddDaughter(fSpectrometerShield);
    fWorld->AddDaughter(fThirdTransportField);

    // Construct volumes
    fWorld->ConstructSelfAndDescendants(true);

    fWorld->WriteSelfAndDesendentsToGDML("test.gdml");

    auto geoManager = std::make_unique<TGeoManager>("MACEGeom", "MACE Geometry");
    geoManager->Import("test.gdml");
    geoManager->Export("test.root");

    return EXIT_SUCCESS;
}
