#include "Simulation/SimMACE/Action/DetectorConstruction.hxx"
#include "Simulation/SimMACE/Field/AcceleratorField.hxx"
#include "Simulation/SimMACE/Field/FirstBendField.hxx"
#include "Simulation/SimMACE/Field/ParallelField.hxx"
#include "Simulation/SimMACE/Field/SecondBendField.hxx"
#include "Simulation/SimMACE/Field/SelectorField.hxx"
#include "Simulation/SimMACE/Field/VerticalField.hxx"

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
    fAcceleratorField = std::make_shared<AcceleratorField>();
    fEMCal = std::make_shared<EMCal>();
    fEMCalField = std::make_shared<EMCalField>();
    fEMCalShield = std::make_shared<EMCalShield>();
    fCDCBody = std::make_shared<CDCBody>();
    fCDCCell = std::make_shared<CDCCell>();
    fCDCFieldWire = std::make_shared<CDCFieldWire>();
    fCDCLayer = std::make_shared<CDCLayer>();
    fCDCSenseWire = std::make_shared<CDCSenseWire>();
    fCDCSensitiveVolume = std::make_shared<CDCSensitiveVolume>();
    fCollimator = std::make_shared<Collimator>();
    fFirstBendField = std::make_shared<FirstBendField>();
    fFirstBendSolenoid = std::make_shared<FirstBendSolenoid>();
    fFirstTransportField = std::make_shared<FirstTransportField>();
    fFirstTransportSolenoid = std::make_shared<FirstTransportSolenoid>();
    fSecondBendField = std::make_shared<SecondBendField>();
    fSecondBendSolenoid = std::make_shared<SecondBendSolenoid>();
    fSecondTransportField = std::make_shared<SecondTransportField>();
    fSecondTransportSolenoid = std::make_shared<SecondTransportSolenoid>();
    fSelectorField = std::make_shared<SelectorField>();
    fSpectrometerField = std::make_shared<SpectrometerField>();
    fSpectrometerMagnet = std::make_shared<SpectrometerMagnet>();
    fSpectrometerShield = std::make_shared<SpectrometerShield>();
    fTarget = std::make_shared<Target>();
    fThirdTransportField = std::make_shared<ThirdTransportField>();
    fThirdTransportSolenoid = std::make_shared<ThirdTransportSolenoid>();
    fVertexDetector = std::make_shared<VertexDetector>();
    fWorld = std::make_shared<World>();

    // Construct hierarchy
    fEMCalField->AddDaughter(fEMCal);
    fEMCalField->AddDaughter(fVertexDetector);
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
    fWorld->AddDaughter(fEMCalField);
    fWorld->AddDaughter(fEMCalShield);
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

    // EMCalSensitiveRegion
    fEMCalSensitiveRegion = new Region("EMCalSensitive", Region::kEMCalSensitive);
    fEMCalSensitiveRegion->SetProductionCuts(defaultCuts);

    fEMCal->RegisterRegion(fEMCalSensitiveRegion);

    // DefaultSolidRegion
    fDefaultSolidRegion = new Region("DefaultSolid", Region::kDefaultSolid);
    fDefaultSolidRegion->SetProductionCuts(defaultCuts);

    fCollimator->RegisterRegion(fDefaultSolidRegion);
    fCDCSenseWire->RegisterRegion(fDefaultSolidRegion);
    fCDCFieldWire->RegisterRegion(fDefaultSolidRegion);
    fCDCBody->RegisterRegion(fDefaultSolidRegion);

    // DefaultGaseousRegion
    fDefaultGaseousRegion = new Region("DefaultGaseous", Region::kDefaultGaseous);
    fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

    fCDCCell->RegisterRegion(fDefaultGaseousRegion);
    fCDCLayer->RegisterRegion(fDefaultGaseousRegion);

    // ShieldRegion
    fShieldRegion = new Region("Shield", Region::kShield);
    fShieldRegion->SetProductionCuts(defaultCuts);

    fSpectrometerShield->RegisterRegion(fShieldRegion);
    fEMCalShield->RegisterRegion(fShieldRegion);

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

    fCDCSensitiveVolume->RegisterRegion(fSpectrometerSensitiveRegion);

    // TargetRegion
    fTargetRegion = new Region("Target", Region::kTarget);
    fTargetRegion->SetProductionCuts(defaultCuts);

    fTarget->RegisterRegion(fTargetRegion);

    // VacuumRegion
    fVacuumRegion = new Region("Vacuum", Region::kVacuum);
    fVacuumRegion->SetProductionCuts(defaultCuts);

    fSelectorField->RegisterRegion(fVacuumRegion);
    fAcceleratorField->RegisterRegion(fVacuumRegion);
    fEMCalField->RegisterRegion(fVacuumRegion);
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
    fEMCalSD = new EMCalSD(fEMCal->GetLogicalVolumeName());
    fEMCal->RegisterSD(fEMCalSD);

    fVertexDetectorSD = new VertexDetectorSD(fVertexDetector->GetLogicalVolumeName());
    fVertexDetector->RegisterSD(fVertexDetectorSD);

    fCDCSD = new CDCSD(fCDCSensitiveVolume->GetLogicalVolumeName());
    fCDCSensitiveVolume->RegisterSD(fCDCSD);
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

    fEMCalField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>>(
        parallelBField, hMin, 6, true);
}

} // namespace MACE::Simulation::SimMACE::Action
