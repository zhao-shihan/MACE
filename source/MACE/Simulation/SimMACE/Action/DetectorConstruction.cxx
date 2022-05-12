#include "MACE/Simulation/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/Simulation/SimMACE/Field/FirstBendField.hxx"
#include "MACE/Simulation/SimMACE/Field/LinacField.hxx"
#include "MACE/Simulation/SimMACE/Field/ParallelField.hxx"
#include "MACE/Simulation/SimMACE/Field/SecondBendField.hxx"
#include "MACE/Simulation/SimMACE/Field/SelectorField.hxx"
#include "MACE/Simulation/SimMACE/Field/VerticalField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4DormandPrince745.hh"
#include "G4EqMagElectricField.hh"
#include "G4IntegrationDriver.hh"
#include "G4NistManager.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

namespace MACE::Simulation::SimMACE::Action {

G4VPhysicalVolume* DetectorConstruction::Construct() {
    ConstructVolumes();
    ConstructMaterials();
    ConstructRegions();
    ConstructSDs();
    ConstructFields();
    return fWorld->GetPhysicalVolume();
}

void DetectorConstruction::ConstructVolumes() {
    // Construct entity objects
    fBeamCounter = std::make_shared<BeamCounter>();
    fBeamDegrader = std::make_shared<BeamDegrader>();
    fCDCBody = std::make_shared<CDCBody>();
    fCDCCell = std::make_shared<CDCCell>();
    fCDCFieldWire = std::make_shared<CDCFieldWire>();
    fCDCLayer = std::make_shared<CDCLayer>();
    fCDCSenseWire = std::make_shared<CDCSenseWire>();
    fCDCSensitiveVolume = std::make_shared<CDCSensitiveVolume>();
    fCollimator = std::make_shared<Collimator>();
    fEMCal = std::make_shared<EMCal>();
    fEMCalField = std::make_shared<EMCalField>();
    fEMCalShield = std::make_shared<EMCalShield>();
    fFirstBendField = std::make_shared<FirstBendField>();
    fFirstBendSolenoid = std::make_shared<FirstBendSolenoid>();
    fFirstTransportField = std::make_shared<FirstTransportField>();
    fFirstTransportSolenoid = std::make_shared<FirstTransportSolenoid>();
    fLinacField = std::make_shared<LinacField>();
    fMCP = std::make_shared<MCP>();
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
    fWorld = std::make_shared<World>();

    // Construct hierarchy
    fCDCBody->AddDaughter(fCDCLayer);
    fCDCCell->AddDaughter(fCDCFieldWire);
    fCDCCell->AddDaughter(fCDCSensitiveVolume);
    fCDCLayer->AddDaughter(fCDCCell);
    fCDCSensitiveVolume->AddDaughter(fCDCSenseWire);
    fEMCalField->AddDaughter(fEMCal);
    fEMCalField->AddDaughter(fMCP);
    fFirstBendField->AddDaughter(fFirstBendSolenoid);
    fFirstTransportField->AddDaughter(fFirstTransportSolenoid);
    fLinacField->AddDaughter(fBeamCounter);
    fLinacField->AddDaughter(fBeamDegrader);
    fLinacField->AddDaughter(fTarget);
    fSecondBendField->AddDaughter(fSecondBendSolenoid);
    fSecondTransportField->AddDaughter(fCollimator);
    fSecondTransportField->AddDaughter(fSecondTransportSolenoid);
    fSecondTransportField->AddDaughter(fSelectorField);
    fSpectrometerField->AddDaughter(fCDCBody);
    fSpectrometerField->AddDaughter(fLinacField);
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

void DetectorConstruction::ConstructMaterials() {
    using namespace MACE::Utility::LiteralUnit::Density;

    auto nist = G4NistManager::Instance();

    auto aluminium = nist->FindOrBuildMaterial("G4_Al");
    fBeamDegrader->RegisterMaterial(aluminium);
    fCDCFieldWire->RegisterMaterial(aluminium);

    auto cdcGas = nist->FindOrBuildMaterial("G4_He");
    fCDCCell->RegisterMaterial(cdcGas);
    fCDCLayer->RegisterMaterial(cdcGas);
    fCDCSensitiveVolume->RegisterMaterial(cdcGas);

    auto cdcShell = nist->BuildMaterialWithNewDensity("CarbonFiber", "G4_C", 1.7_g_cm3);
    fCDCBody->RegisterMaterial(cdcShell);

    auto copper = nist->FindOrBuildMaterial("G4_Cu");
    fCollimator->RegisterMaterial(copper);
    fFirstBendSolenoid->RegisterMaterial(copper);
    fFirstTransportSolenoid->RegisterMaterial(copper);
    fSecondBendSolenoid->RegisterMaterial(copper);
    fSecondTransportSolenoid->RegisterMaterial(copper);
    fThirdTransportSolenoid->RegisterMaterial(copper);

    auto csI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    fEMCal->RegisterMaterial(csI);

    auto iron = nist->FindOrBuildMaterial("G4_Fe");
    fSpectrometerMagnet->RegisterMaterial(iron);

    auto lead = nist->FindOrBuildMaterial("G4_Pb");
    fEMCalShield->RegisterMaterial(lead);
    fSpectrometerShield->RegisterMaterial(lead);

    auto mcpMaterial = nist->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4_g_cm3);
    fMCP->RegisterMaterial(mcpMaterial);

    auto plasticScitillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    fBeamCounter->RegisterMaterial(plasticScitillator);

    auto silicaAerogel = nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30_mg_cm3);
    fTarget->RegisterMaterial(silicaAerogel);

    auto tungsten = nist->FindOrBuildMaterial("G4_W");
    fCDCSenseWire->RegisterMaterial(tungsten);

    auto vacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3);
    fEMCalField->RegisterMaterial(vacuum);
    fFirstBendField->RegisterMaterial(vacuum);
    fFirstTransportField->RegisterMaterial(vacuum);
    fLinacField->RegisterMaterial(vacuum);
    fSecondBendField->RegisterMaterial(vacuum);
    fSecondTransportField->RegisterMaterial(vacuum);
    fSelectorField->RegisterMaterial(vacuum);
    fSpectrometerField->RegisterMaterial(vacuum);
    fThirdTransportField->RegisterMaterial(vacuum);
    fWorld->RegisterMaterial(vacuum);
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

    fBeamCounter->RegisterRegion(fDefaultSolidRegion);
    fBeamDegrader->RegisterRegion(fDefaultSolidRegion);
    fCDCBody->RegisterRegion(fDefaultSolidRegion);
    fCDCFieldWire->RegisterRegion(fDefaultSolidRegion);
    fCDCSenseWire->RegisterRegion(fDefaultSolidRegion);
    fCollimator->RegisterRegion(fDefaultSolidRegion);

    // DefaultGaseousRegion
    fDefaultGaseousRegion = new Region("DefaultGaseous", Region::kDefaultGaseous);
    fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

    fCDCCell->RegisterRegion(fDefaultGaseousRegion);
    fCDCLayer->RegisterRegion(fDefaultGaseousRegion);

    // ShieldRegion
    fShieldRegion = new Region("Shield", Region::kShield);
    fShieldRegion->SetProductionCuts(defaultCuts);

    fEMCalShield->RegisterRegion(fShieldRegion);
    fSpectrometerShield->RegisterRegion(fShieldRegion);

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

    fEMCalField->RegisterRegion(fVacuumRegion);
    fFirstBendField->RegisterRegion(fVacuumRegion);
    fFirstTransportField->RegisterRegion(fVacuumRegion);
    fLinacField->RegisterRegion(fVacuumRegion);
    fSecondBendField->RegisterRegion(fVacuumRegion);
    fSecondTransportField->RegisterRegion(fVacuumRegion);
    fSelectorField->RegisterRegion(fVacuumRegion);
    fSpectrometerField->RegisterRegion(fVacuumRegion);
    fThirdTransportField->RegisterRegion(fVacuumRegion);

    // MCPSensitiveRegion
    fMCPSensitiveRegion = new Region("MCPSensitive", Region::kMCPSensitive);
    fMCPSensitiveRegion->SetProductionCuts(defaultCuts);

    fMCP->RegisterRegion(fMCPSensitiveRegion);
}

void DetectorConstruction::ConstructSDs() {
    fCDCSD = new CDCSD(fCDCSensitiveVolume->GetLogicalVolume()->GetName());
    fCDCSensitiveVolume->RegisterSD(fCDCSD);

    fEMCalSD = new EMCalSD(fEMCal->GetLogicalVolume()->GetName());
    fEMCal->RegisterSD(fEMCalSD);

    fMCPSD = new MCPSD(fMCP->GetLogicalVolume()->GetName());
    fMCP->RegisterSD(fMCPSD);
}

void DetectorConstruction::ConstructFields() {
    using namespace MACE::Utility::LiteralUnit;
    using namespace Field;

    constexpr G4double hMin = 1_um;

    constexpr G4double defaultB = 0.1_T;
    auto parallelBField = new ParallelField(defaultB);
    auto verticalBField = new VerticalField(defaultB);

    fSpectrometerField->RegisterField<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>>(
        parallelBField, hMin, 6, true);

    fLinacField->RegisterField<
        LinacField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>>(
        new LinacField(), hMin, 8, true);

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
