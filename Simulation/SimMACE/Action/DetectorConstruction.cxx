#include "SimMACE/Action/DetectorConstruction.hxx"
#include "SimMACE/Field/AcceleratorField.hxx"
#include "SimMACE/Field/FirstBendField.hxx"
#include "SimMACE/Field/ParallelField.hxx"
#include "SimMACE/Field/SecondBendField.hxx"
#include "SimMACE/Field/SelectorField.hxx"
#include "SimMACE/Field/VerticalField.hxx"

#include "G4DormandPrince745.hh"
#include "G4EqMagElectricField.hh"
#include "G4IntegrationDriver.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4SDManager.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

namespace MACE::Simulation::SimMACE::Action {

G4VPhysicalVolume* DetectorConstruction::Construct() {
    ConstructVolumes();
    ConstructRegions();
    ConstructSDs();
    ConstructFields();
    return fWorld->GetPhysicalVolume();
}

void DetectorConstruction::ConstructVolumes() {
    // Construct entity objects
    fCalorimeter = std::make_shared<Calorimeter>();
    fVertexDetector = std::make_shared<VertexDetector>();
    fFirstBendSolenoid = std::make_shared<FirstBendSolenoid>();
    fFirstTransportSolenoid = std::make_shared<FirstTransportSolenoid>();
    fSecondBendSolenoid = std::make_shared<SecondBendSolenoid>();
    fCollimator = std::make_shared<Collimator>();
    fSecondTransportSolenoid = std::make_shared<SecondTransportSolenoid>();
    fSelectorField = std::make_shared<SelectorField>();
    fTarget = std::make_shared<Target>();
    fSpectrometerSenseWires = std::make_shared<SpectrometerSenseWires>();
    fSpectrometerFieldWires = std::make_shared<SpectrometerFieldWires>();
    fSpectrometerSensitiveVolumes = std::make_shared<SpectrometerSensitiveVolumes>();
    fSpectrometerCells = std::make_shared<SpectrometerCells>();
    fSpectrometerReadoutLayers = std::make_shared<SpectrometerReadoutLayers>();
    fAcceleratorField = std::make_shared<AcceleratorField>();
    fSpectrometerBody = std::make_shared<SpectrometerBody>();
    fSpectrometerMagnet = std::make_shared<SpectrometerMagnet>();
    fThirdTransportSolenoid = std::make_shared<ThirdTransportSolenoid>();
    fCalorimeterField = std::make_shared<CalorimeterField>();
    fCalorimeterShield = std::make_shared<CalorimeterShield>();
    fFirstBendField = std::make_shared<FirstBendField>();
    fFirstTransportField = std::make_shared<FirstTransportField>();
    fSecondBendField = std::make_shared<SecondBendField>();
    fSecondTransportField = std::make_shared<SecondTransportField>();
    fSpectrometerField = std::make_shared<SpectrometerField>();
    fSpectrometerShield = std::make_shared<SpectrometerShield>();
    fThirdTransportField = std::make_shared<ThirdTransportField>();
    fWorld = std::make_shared<World>();

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
    fSpectrometerSensitiveVolumes->AddDaughter(fSpectrometerSenseWires);
    fSpectrometerCells->AddDaughter(fSpectrometerFieldWires);
    fSpectrometerCells->AddDaughter(fSpectrometerSensitiveVolumes);
    fSpectrometerReadoutLayers->AddDaughter(fSpectrometerCells);
    fSpectrometerBody->AddDaughter(fSpectrometerReadoutLayers);
    fSpectrometerField->AddDaughter(fAcceleratorField);
    fSpectrometerField->AddDaughter(fSpectrometerBody);
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
    fWorld->ConstructSelfAndDescendants(fCheckOverlaps);
}

void DetectorConstruction::ConstructRegions() {
    auto defaultCuts = G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts();

    // CalorimeterSensitiveRegion
    fCalorimeterSensitiveRegion = new Region("CalorimeterSensitive", Region::kCalorimeterSensitive);
    fCalorimeterSensitiveRegion->SetProductionCuts(defaultCuts);

    fCalorimeter->RegisterRegion(fCalorimeterSensitiveRegion);

    // DefaultSolidRegion
    fDefaultSolidRegion = new Region("DefaultSolid", Region::kDefaultSolid);
    fDefaultSolidRegion->SetProductionCuts(defaultCuts);

    fCollimator->RegisterRegion(fDefaultSolidRegion);
    fSpectrometerSenseWires->RegisterRegion(fDefaultSolidRegion);
    fSpectrometerFieldWires->RegisterRegion(fDefaultSolidRegion);
    fSpectrometerBody->RegisterRegion(fDefaultSolidRegion);

    // DefaultGaseousRegion
    fDefaultGaseousRegion = new Region("DefaultGaseous", Region::kDefaultGaseous);
    fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

    fSpectrometerCells->RegisterRegion(fDefaultGaseousRegion);
    fSpectrometerReadoutLayers->RegisterRegion(fDefaultGaseousRegion);

    // ShieldRegion
    fShieldRegion = new Region("Shield", Region::kShield);
    fShieldRegion->SetProductionCuts(defaultCuts);

    fSpectrometerShield->RegisterRegion(fShieldRegion);
    fCalorimeterShield->RegisterRegion(fShieldRegion);

    // SolenoidOrMagnetRegion
    fSolenoidOrMagnetRegion = new Region("SolenoidOrMagnet", Region::kSolenoidOrMagnet);
    fSolenoidOrMagnetRegion->SetProductionCuts(defaultCuts);

    fFirstBendSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);
    fFirstTransportSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);
    fSecondBendSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);
    fSecondTransportSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);
    fSpectrometerMagnet->RegisterRegion(fSolenoidOrMagnetRegion);
    fThirdTransportSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);

    // SpectrometerSensitiveRegion
    fSpectrometerSensitiveRegion = new Region("SpectrometerSensitive", Region::kSpectrometerSensitive);
    fSpectrometerSensitiveRegion->SetProductionCuts(defaultCuts);

    fSpectrometerSensitiveVolumes->RegisterRegion(fSpectrometerSensitiveRegion);

    // TargetRegion
    fTargetRegion = new Region("Target", Region::kTarget);
    fTargetRegion->SetProductionCuts(defaultCuts);

    fTarget->RegisterRegion(fTargetRegion);

    // VacuumRegion
    fVacuumRegion = new Region("Vacuum", Region::kVacuum);
    fVacuumRegion->SetProductionCuts(defaultCuts);

    fSelectorField->RegisterRegion(fVacuumRegion);
    fAcceleratorField->RegisterRegion(fVacuumRegion);
    fCalorimeterField->RegisterRegion(fVacuumRegion);
    fFirstBendField->RegisterRegion(fVacuumRegion);
    fFirstTransportField->RegisterRegion(fVacuumRegion);
    fSecondBendField->RegisterRegion(fVacuumRegion);
    fSecondTransportField->RegisterRegion(fVacuumRegion);
    fSpectrometerField->RegisterRegion(fVacuumRegion);
    fThirdTransportField->RegisterRegion(fVacuumRegion);

    // VertexDetectorSensitiveRegion
    fVertexDetectorSensitiveRegion = new Region("VertexDetectorSensitive", Region::kVertexDetectorSensitive);
    fVertexDetectorSensitiveRegion->SetProductionCuts(defaultCuts);

    fVertexDetector->RegisterRegion(fVertexDetectorSensitiveRegion);
}

void DetectorConstruction::ConstructSDs() {
    fCalorimeterSD = new CalorimeterSD(fCalorimeter->GetLogicalVolumeName());
    fCalorimeter->RegisterSD(fCalorimeterSD);

    fVertexDetectorSD = new VertexDetectorSD(fVertexDetector->GetLogicalVolumeName());
    fVertexDetector->RegisterSD(fVertexDetectorSD);

    fSpectrometerSD = new SpectrometerSD(fSpectrometerSensitiveVolumes->GetLogicalVolumeName());
    fSpectrometerSensitiveVolumes->RegisterSD(fSpectrometerSD);
}

void DetectorConstruction::ConstructFields() {
    using namespace MACE::Utility::LiteralUnit;
    using namespace Field;

    constexpr G4double hMin = 100_um;

    constexpr G4double defaultB = 0.1_T;
    auto parallelBField = new ParallelField(defaultB);
    auto verticalBField = new VerticalField(defaultB);

    fSpectrometerField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>>(
        parallelBField, hMin, 6, true);

    fAcceleratorField->RegisterField<
        AcceleratorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>>(
        new AcceleratorField(), hMin, 8, true);

    fFirstTransportField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>>(
        parallelBField, hMin, 6, true);

    fFirstBendField->RegisterField<
        FirstBendField,
        G4TMagFieldEquation<Field::FirstBendField>,
        G4TDormandPrince45<G4TMagFieldEquation<Field::FirstBendField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<Field::FirstBendField>>>>(
        new FirstBendField(), hMin, 6, true);

    fSecondTransportField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>>(
        verticalBField, hMin, 6, true);

    fSelectorField->RegisterField<
        SelectorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>>(
        new SelectorField(), hMin, 8, true);

    fSecondBendField->RegisterField<
        SecondBendField,
        G4TMagFieldEquation<Field::SecondBendField>,
        G4TDormandPrince45<G4TMagFieldEquation<Field::SecondBendField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<Field::SecondBendField>>>>(
        new SecondBendField(), hMin, 6, true);

    fThirdTransportField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>>(
        parallelBField, hMin, 6, true);

    fCalorimeterField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>>(
        parallelBField, hMin, 6, true);
}

} // namespace MACE::Simulation::SimMACE::Action
