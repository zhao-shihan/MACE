#include "MACE/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/SimMACE/Field/FirstBendField.hxx"
#include "MACE/SimMACE/Field/LinacField.hxx"
#include "MACE/SimMACE/Field/ParallelField.hxx"
#include "MACE/SimMACE/Field/SecondBendField.hxx"
#include "MACE/SimMACE/Field/SelectorField.hxx"
#include "MACE/SimMACE/Field/VerticalField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4DormandPrince745.hh"
#include "G4EqMagElectricField.hh"
#include "G4IntegrationDriver.hh"
#include "G4NistManager.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

namespace MACE::SimMACE::Action {

DetectorConstruction::DetectorConstruction() :
    NonCopyableBase(),
    G4VUserDetectorConstruction(),
    fCheckOverlap(false),
    fBeamDegrader(nullptr),
    fBeamMonitor(nullptr),
    fCDCBody(nullptr),
    fCDCCell(nullptr),
    fCDCFieldWire(nullptr),
    fCDCLayer(nullptr),
    fCDCSenseWire(nullptr),
    fCDCSensitiveVolume(nullptr),
    fCollimator(nullptr),
    fEMCal(nullptr),
    fEMCalField(nullptr),
    fEMCalShield(nullptr),
    fFirstBendField(nullptr),
    fFirstBendSolenoid(nullptr),
    fFirstTransportField(nullptr),
    fFirstTransportSolenoid(nullptr),
    fLinacField(nullptr),
    fMCP(nullptr),
    fSecondBendField(nullptr),
    fSecondBendSolenoid(nullptr),
    fSecondTransportField(nullptr),
    fSecondTransportSolenoid(nullptr),
    fSelectorField(nullptr),
    fSpectrometerField(nullptr),
    fSpectrometerMagnet(nullptr),
    fSpectrometerShield(nullptr),
    fTarget(nullptr),
    fThirdTransportField(nullptr),
    fThirdTransportSolenoid(nullptr),
    fWorld(nullptr),
    fEMCalSensitiveRegion(nullptr),
    fDefaultSolidRegion(nullptr),
    fDefaultGaseousRegion(nullptr),
    fShieldRegion(nullptr),
    fSolenoidOrMagnetRegion(nullptr),
    fSpectrometerSensitiveRegion(nullptr),
    fTargetRegion(nullptr),
    fVacuumRegion(nullptr),
    fMCPSensitiveRegion(nullptr),
    fCDCSD(nullptr),
    fEMCalSD(nullptr),
    fMCPSD(nullptr) {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    ConstructVolumes();
    ConstructMaterials();
    ConstructRegions();
    ConstructSDs();
    ConstructFields();
    return fWorld->GetPhysicalVolume();
}

void DetectorConstruction::ConstructVolumes() {
    using namespace Core::Geometry::Entity::Fast;

    // Construct entity objects
    fBeamDegrader = std::make_shared<BeamDegrader>();
    fBeamMonitor = std::make_shared<BeamMonitor>();
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
    fLinacField->AddDaughter(fBeamDegrader);
    fLinacField->AddDaughter(fBeamMonitor);
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
    fWorld->ConstructSelfAndDescendants(fCheckOverlap);
}

void DetectorConstruction::ConstructMaterials() {
    using namespace MACE::Utility::LiteralUnit::Density;

    const auto nist = G4NistManager::Instance();

    const auto aluminium = nist->FindOrBuildMaterial("G4_Al");
    fBeamDegrader->RegisterMaterial(aluminium);
    fCDCFieldWire->RegisterMaterial(aluminium);

    const auto cdcGas = nist->FindOrBuildMaterial("G4_He");
    fCDCCell->RegisterMaterial(cdcGas);
    fCDCLayer->RegisterMaterial(cdcGas);
    fCDCSensitiveVolume->RegisterMaterial(cdcGas);

    const auto cdcShell = nist->BuildMaterialWithNewDensity("CarbonFiber", "G4_C", 1.7_g_cm3);
    fCDCBody->RegisterMaterial(cdcShell);

    const auto copper = nist->FindOrBuildMaterial("G4_Cu");
    fCollimator->RegisterMaterial(copper);
    fFirstBendSolenoid->RegisterMaterial(copper);
    fFirstTransportSolenoid->RegisterMaterial(copper);
    fSecondBendSolenoid->RegisterMaterial(copper);
    fSecondTransportSolenoid->RegisterMaterial(copper);
    fThirdTransportSolenoid->RegisterMaterial(copper);

    const auto csI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    fEMCal->RegisterMaterial(csI);

    const auto iron = nist->FindOrBuildMaterial("G4_Fe");
    fSpectrometerMagnet->RegisterMaterial(iron);

    const auto lead = nist->FindOrBuildMaterial("G4_Pb");
    fEMCalShield->RegisterMaterial(lead);
    fSpectrometerShield->RegisterMaterial(lead);

    const auto mcpMaterial = nist->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4_g_cm3);
    fMCP->RegisterMaterial(mcpMaterial);

    const auto plasticScitillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    fBeamMonitor->RegisterMaterial(plasticScitillator);

    const auto silicaAerogel = nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30_mg_cm3);
    fTarget->RegisterMaterial(silicaAerogel);

    const auto tungsten = nist->FindOrBuildMaterial("G4_W");
    fCDCSenseWire->RegisterMaterial(tungsten);

    const auto vacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3);
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
    const auto defaultCuts = G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts();

    // EMCalSensitiveRegion
    fEMCalSensitiveRegion = new Region("EMCalSensitive", RegionType::EMCalSensitive);
    fEMCalSensitiveRegion->SetProductionCuts(defaultCuts);

    fEMCal->RegisterRegion(fEMCalSensitiveRegion);

    // DefaultSolidRegion
    fDefaultSolidRegion = new Region("DefaultSolid", RegionType::DefaultSolid);
    fDefaultSolidRegion->SetProductionCuts(defaultCuts);

    fBeamDegrader->RegisterRegion(fDefaultSolidRegion);
    fBeamMonitor->RegisterRegion(fDefaultSolidRegion);
    fCDCBody->RegisterRegion(fDefaultSolidRegion);
    fCDCFieldWire->RegisterRegion(fDefaultSolidRegion);
    fCDCSenseWire->RegisterRegion(fDefaultSolidRegion);
    fCollimator->RegisterRegion(fDefaultSolidRegion);

    // DefaultGaseousRegion
    fDefaultGaseousRegion = new Region("DefaultGaseous", RegionType::DefaultGaseous);
    fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

    fCDCCell->RegisterRegion(fDefaultGaseousRegion);
    fCDCLayer->RegisterRegion(fDefaultGaseousRegion);

    // ShieldRegion
    fShieldRegion = new Region("Shield", RegionType::Shield);
    fShieldRegion->SetProductionCuts(defaultCuts);

    fEMCalShield->RegisterRegion(fShieldRegion);
    fSpectrometerShield->RegisterRegion(fShieldRegion);

    // SolenoidOrMagnetRegion
    fSolenoidOrMagnetRegion = new Region("SolenoidOrMagnet", RegionType::SolenoidOrMagnet);
    fSolenoidOrMagnetRegion->SetProductionCuts(defaultCuts);

    fFirstBendSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);
    fFirstTransportSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);
    fSecondBendSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);
    fSecondTransportSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);
    fSpectrometerMagnet->RegisterRegion(fSolenoidOrMagnetRegion);
    fThirdTransportSolenoid->RegisterRegion(fSolenoidOrMagnetRegion);

    // SpectrometerSensitiveRegion
    fSpectrometerSensitiveRegion = new Region("SpectrometerSensitive", RegionType::SpectrometerSensitive);
    fSpectrometerSensitiveRegion->SetProductionCuts(defaultCuts);

    fCDCSensitiveVolume->RegisterRegion(fSpectrometerSensitiveRegion);

    // TargetRegion
    fTargetRegion = new Region("Target", RegionType::Target);
    fTargetRegion->SetProductionCuts(defaultCuts);

    fTarget->RegisterRegion(fTargetRegion);

    // VacuumRegion
    fVacuumRegion = new Region("Vacuum", RegionType::Vacuum);
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
    fMCPSensitiveRegion = new Region("MCPSensitive", RegionType::MCPSensitive);
    fMCPSensitiveRegion->SetProductionCuts(defaultCuts);

    fMCP->RegisterRegion(fMCPSensitiveRegion);
}

void DetectorConstruction::ConstructSDs() {
    fCDCSD = new SD::CDCSD(fCDCSensitiveVolume->GetLogicalVolume()->GetName());
    fCDCSensitiveVolume->RegisterSD(fCDCSD);

    fEMCalSD = new SD::EMCalSD(fEMCal->GetLogicalVolume()->GetName());
    fEMCal->RegisterSD(fEMCalSD);

    fMCPSD = new SD::MCPSD(fMCP->GetLogicalVolume()->GetName());
    fMCP->RegisterSD(fMCPSD);
}

void DetectorConstruction::ConstructFields() {
    using namespace MACE::Utility::LiteralUnit;
    using namespace Field;

    constexpr G4double hMin = 1_um;

    constexpr G4double defaultB = 0.1_T;
    const auto parallelBField = new ParallelField(defaultB);
    const auto verticalBField = new VerticalField(defaultB);

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

} // namespace MACE::SimMACE::Action
