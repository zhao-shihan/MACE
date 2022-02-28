#include "SimMACE/Action/DetectorConstruction.hxx"

using namespace MACE::SimMACE::Action;

G4VPhysicalVolume* DetectorConstruction::Construct() {
    ConstructVolumes();
    ConstructRegions();
    ConstructSDs();
    ConstructFields();
    return fWorld->GetPhysicalVolume();
}

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

void DetectorConstruction::ConstructVolumes() {
    // Construct entity objects
    fCalorimeter = std::make_shared<Geometry::Entity::Fast::Calorimeter>();
    fVertexDetector = std::make_shared<Geometry::Entity::Fast::VertexDetector>();
    fFirstBendSolenoid = std::make_shared<Geometry::Entity::Fast::FirstBendSolenoid>();
    fFirstTransportSolenoid = std::make_shared<Geometry::Entity::Fast::FirstTransportSolenoid>();
    fSecondBendSolenoid = std::make_shared<Geometry::Entity::Fast::SecondBendSolenoid>();
    fCollimator = std::make_shared<Geometry::Entity::Fast::Collimator>();
    fSecondTransportSolenoid = std::make_shared<Geometry::Entity::Fast::SecondTransportSolenoid>();
    fSelectorField = std::make_shared<Geometry::Entity::Fast::SelectorField>();
    fTarget = std::make_shared<Geometry::Entity::Fast::Target>();
    fSpectrometerCells = std::make_shared<Geometry::Entity::Fast::SpectrometerCells>();
    fSpectrometerReadoutLayers = std::make_shared<Geometry::Entity::Fast::SpectrometerReadoutLayers>();
    fAcceleratorField = std::make_shared<Geometry::Entity::Fast::AcceleratorField>();
    fSpectrometerBody = std::make_shared<Geometry::Entity::Fast::SpectrometerBody>();
    fSpectrometerMagnet = std::make_shared<Geometry::Entity::Fast::SpectrometerMagnet>();
    fThirdTransportSolenoid = std::make_shared<Geometry::Entity::Fast::ThirdTransportSolenoid>();
    fCalorimeterField = std::make_shared<Geometry::Entity::Fast::CalorimeterField>();
    fCalorimeterShield = std::make_shared<Geometry::Entity::Fast::CalorimeterShield>();
    fFirstBendField = std::make_shared<Geometry::Entity::Fast::FirstBendField>();
    fFirstTransportField = std::make_shared<Geometry::Entity::Fast::FirstTransportField>();
    fSecondBendField = std::make_shared<Geometry::Entity::Fast::SecondBendField>();
    fSecondTransportField = std::make_shared<Geometry::Entity::Fast::SecondTransportField>();
    fSpectrometerField = std::make_shared<Geometry::Entity::Fast::SpectrometerField>();
    fSpectrometerShield = std::make_shared<Geometry::Entity::Fast::SpectrometerShield>();
    fThirdTransportField = std::make_shared<Geometry::Entity::Fast::ThirdTransportField>();
    fWorld = std::make_shared<Geometry::Entity::Fast::World>();

    // Construct hierarchy
    fCalorimeterField->AddDaughter(fCalorimeter);
    fCalorimeterField->AddDaughter(fVertexDetector);
    fFirstBendField->AddDaughter(fFirstBendSolenoid);
    fFirstTransportField->AddDaughter(fFirstTransportSolenoid);
    fSecondBendField->AddDaughter(fSecondBendSolenoid);
    fSecondTransportField->AddDaughter(fCollimator);
    fSecondTransportField->AddDaughter(fSecondTransportSolenoid);
    fSecondTransportField->AddDaughter(fSelectorField);
    fSpectrometerField->AddDaughter(fAcceleratorField);
    fSpectrometerField->AddDaughter(fSpectrometerBody);
    fSpectrometerField->AddDaughter(fSpectrometerMagnet);
    fThirdTransportField->AddDaughter(fThirdTransportSolenoid);
    fAcceleratorField->AddDaughter(fTarget);
    fSpectrometerBody->AddDaughter(fSpectrometerReadoutLayers);
    fSpectrometerReadoutLayers->AddDaughter(fSpectrometerCells);
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
    fWorld->ConstructSelfAndDescendants(fCheckOverlaps);
}

#include "SimMACE/Utility/Region.hxx"

void DetectorConstruction::ConstructRegions() {
    // CalorimeterSensitiveRegion
    fCalorimeterSensitiveRegion = std::make_unique<Region>("CalorimeterSensitive", kCalorimeterSensitiveRegion);
    fCalorimeter->RegisterRegion(fCalorimeterSensitiveRegion.get());

    // DefaultSolidRegion
    fDefaultSolidRegion = std::make_unique<Region>("DefaultSolid", kDefaultSolidRegion);
    fCollimator->RegisterRegion(fDefaultSolidRegion.get());
    fSpectrometerBody->RegisterRegion(fDefaultSolidRegion.get());

    // DefaultGaseousRegion
    fDefaultGaseousRegion = std::make_unique<Region>("DefaultGaseous", kDefaultGaseousRegion);
    fSpectrometerReadoutLayers->RegisterRegion(fDefaultGaseousRegion.get());
    fWorld->RegisterRegion(fDefaultGaseousRegion.get());

    // ShieldRegion
    fShieldRegion = std::make_unique<Region>("Shield", kShieldRegion);
    fSpectrometerShield->RegisterRegion(fShieldRegion.get());
    fCalorimeterShield->RegisterRegion(fShieldRegion.get());

    // SolenoidOrMagnetRegion
    fSolenoidOrMagnetRegion = std::make_unique<Region>("SolenoidOrMagnet", kSolenoidOrMagnetRegion);
    fFirstBendSolenoid->RegisterRegion(fSolenoidOrMagnetRegion.get());
    fFirstTransportSolenoid->RegisterRegion(fSolenoidOrMagnetRegion.get());
    fSecondBendSolenoid->RegisterRegion(fSolenoidOrMagnetRegion.get());
    fSecondTransportSolenoid->RegisterRegion(fSolenoidOrMagnetRegion.get());
    fSpectrometerMagnet->RegisterRegion(fSolenoidOrMagnetRegion.get());
    fThirdTransportSolenoid->RegisterRegion(fSolenoidOrMagnetRegion.get());

    // SpectrometerSensitiveRegion
    fSpectrometerSensitiveRegion = std::make_unique<Region>("SpectrometerSensitive", kSpectrometerSensitiveRegion);
    fSpectrometerCells->RegisterRegion(fSpectrometerSensitiveRegion.get());

    // TargetRegion
    fTargetRegion = std::make_unique<Region>("Target", kTargetRegion);
    fTarget->RegisterRegion(fTargetRegion.get());

    // VacuumRegion
    fVacuumRegion = std::make_unique<Region>("Vacuum", kVacuumRegion);
    fSelectorField->RegisterRegion(fVacuumRegion.get());
    fAcceleratorField->RegisterRegion(fVacuumRegion.get());
    fCalorimeterField->RegisterRegion(fVacuumRegion.get());
    fFirstBendField->RegisterRegion(fVacuumRegion.get());
    fFirstTransportField->RegisterRegion(fVacuumRegion.get());
    fSecondBendField->RegisterRegion(fVacuumRegion.get());
    fSecondTransportField->RegisterRegion(fVacuumRegion.get());
    fSpectrometerField->RegisterRegion(fVacuumRegion.get());
    fThirdTransportField->RegisterRegion(fVacuumRegion.get());

    // VertexDetectorSensitiveRegion
    fVertexDetectorSensitiveRegion = std::make_unique<Region>("VertexDetectorSensitive", kVertexDetectorSensitiveRegion);
    fVertexDetector->RegisterRegion(fVertexDetectorSensitiveRegion.get());
}

#include "G4SDManager.hh"

#include "SimMACE/SD/CalorimeterSD.hxx"
#include "SimMACE/SD/VertexDetectorSD.hxx"
#include "SimMACE/SD/SpectrometerCellSD.hxx"

void DetectorConstruction::ConstructSDs() {
    const auto& calorimeterName = fCalorimeter->GetLogicalVolumeName();
    fCalorimeter->RegisterSensitiveDetector(new CalorimeterSD(calorimeterName, calorimeterName + "HC"));
    const auto& vertexDetectorName = fVertexDetector->GetLogicalVolumeName();
    fVertexDetector->RegisterSensitiveDetector(new VertexDetectorSD(vertexDetectorName, vertexDetectorName + "HC"));
    const auto& spectrometerCellName = fSpectrometerCells->GetLogicalVolumeName();
    fSpectrometerCells->RegisterSensitiveDetector(new SpectrometerCellSD(spectrometerCellName, spectrometerCellName + "HC"));
}

#include "G4FieldManager.hh"
#include "G4TMagFieldEquation.hh"
#include "G4EqMagElectricField.hh"
#include "G4TDormandPrince45.hh"
#include "G4DormandPrince745.hh"
#include "G4IntegrationDriver.hh"
#include "G4ChordFinder.hh"

#include "SimMACE/Field/AcceleratorField.hxx"
#include "SimMACE/Field/FirstBendField.hxx"
#include "SimMACE/Field/ParallelField.hxx"
#include "SimMACE/Field/SecondBendField.hxx"
#include "SimMACE/Field/SelectorField.hxx"
#include "SimMACE/Field/VerticalField.hxx"

void DetectorConstruction::ConstructFields() {
    constexpr G4double hMin = 100_um;

    constexpr G4double defaultB = 0.1_T;
    auto parallelBField = new ParallelField(defaultB);
    auto verticalBField = new VerticalField(defaultB);

    fSpectrometerField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(parallelBField, hMin, 6);

    fAcceleratorField->RegisterField<
        AcceleratorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(new AcceleratorField(), hMin, 8);

    fFirstTransportField->RegisterField <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(parallelBField, hMin, 6);

    fFirstBendField->RegisterField<
        FirstBendField,
        G4TMagFieldEquation<Field::FirstBendField>,
        G4TDormandPrince45<G4TMagFieldEquation<Field::FirstBendField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<Field::FirstBendField>>>
    >(new FirstBendField(), hMin, 6);

    fSecondTransportField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(verticalBField, hMin, 6);

    fSelectorField->RegisterField <
        SelectorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(new SelectorField(), hMin, 8);

    fSecondBendField->RegisterField <
        SecondBendField,
        G4TMagFieldEquation<Field::SecondBendField>,
        G4TDormandPrince45<G4TMagFieldEquation<Field::SecondBendField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<Field::SecondBendField>>>
    >(new SecondBendField(), hMin, 6);

    fThirdTransportField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(parallelBField, hMin, 6);

    fCalorimeterField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(parallelBField, hMin, 6);
}
