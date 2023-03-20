#include "MACE/SimMACE/Action/DetectorConstruction.hxx"
#include "MACE/SimMACE/Field/FirstBendField.hxx"
#include "MACE/SimMACE/Field/LinacField.hxx"
#include "MACE/SimMACE/Field/ParallelField.hxx"
#include "MACE/SimMACE/Field/SecondBendField.hxx"
#include "MACE/SimMACE/Field/SelectorField.hxx"
#include "MACE/SimMACE/Field/VerticalField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4EqMagElectricField.hh"
#include "G4InterpolationDriver.hh"
#include "G4NistManager.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

namespace MACE::SimMACE::inline Action {

DetectorConstruction::DetectorConstruction() :
    NonMoveableBase(),
    G4VUserDetectorConstruction(),
    fCheckOverlap(false),

    fWorld(std::make_shared<Detector::Geometry::Fast::World>()),

    fCDCFieldWireRegion(nullptr),
    fCDCSenseWireRegion(nullptr),
    fDefaultGaseousRegion(nullptr),
    fDefaultSolidRegion(nullptr),
    fEMCalSensitiveRegion(nullptr),
    fMCPSensitiveRegion(nullptr),
    fShieldRegion(nullptr),
    fSolenoidOrMagnetRegion(nullptr),
    fSpectrometerSensitiveRegion(nullptr),
    fTargetRegion(nullptr),
    fVacuumRegion(nullptr),

    fCDCSD(nullptr),
    fEMCalSD(nullptr),
    fMCPSD(nullptr) {}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    // 1

    auto& emCalField = fWorld->NewDaughter<Detector::Geometry::Fast::EMCalField>(fCheckOverlap);
    auto& emCalShield = fWorld->NewDaughter<Detector::Geometry::Fast::EMCalShield>(fCheckOverlap);
    auto& firstBendField = fWorld->NewDaughter<Detector::Geometry::Fast::FirstBendField>(fCheckOverlap);
    auto& firstTransportField = fWorld->NewDaughter<Detector::Geometry::Fast::FirstTransportField>(fCheckOverlap);
    auto& secondBendField = fWorld->NewDaughter<Detector::Geometry::Fast::SecondBendField>(fCheckOverlap);
    auto& secondTransportField = fWorld->NewDaughter<Detector::Geometry::Fast::SecondTransportField>(fCheckOverlap);
    auto& spectrometerField = fWorld->NewDaughter<Detector::Geometry::Fast::SpectrometerField>(fCheckOverlap);
    auto& spectrometerShield = fWorld->NewDaughter<Detector::Geometry::Fast::SpectrometerShield>(fCheckOverlap);
    auto& thirdTransportField = fWorld->NewDaughter<Detector::Geometry::Fast::ThirdTransportField>(fCheckOverlap);

    // 2

    auto& emCal = emCalField.NewDaughter<Detector::Geometry::Fast::EMCal>(fCheckOverlap);
    auto& mcp = emCalField.NewDaughter<Detector::Geometry::Fast::MCP>(fCheckOverlap);

    auto& firstBendSolenoid = firstBendField.NewDaughter<Detector::Geometry::Fast::FirstBendSolenoid>(fCheckOverlap);

    auto& firstTransportSolenoid = firstTransportField.NewDaughter<Detector::Geometry::Fast::FirstTransportSolenoid>(fCheckOverlap);

    auto& secondBendSolenoid = secondBendField.NewDaughter<Detector::Geometry::Fast::SecondBendSolenoid>(fCheckOverlap);

    auto& collimator = secondTransportField.NewDaughter<Detector::Geometry::Fast::Collimator>(fCheckOverlap);
    auto& secondTransportSolenoid = secondTransportField.NewDaughter<Detector::Geometry::Fast::SecondTransportSolenoid>(fCheckOverlap);
    auto& selectorField = secondTransportField.NewDaughter<Detector::Geometry::Fast::SelectorField>(fCheckOverlap);

    auto& cdcBody = spectrometerField.NewDaughter<Detector::Geometry::Fast::CDCBody>(fCheckOverlap);
    auto& linacField = spectrometerField.NewDaughter<Detector::Geometry::Fast::LinacField>(fCheckOverlap);
    auto& spectrometerMagnet = spectrometerField.NewDaughter<Detector::Geometry::Fast::SpectrometerMagnet>(fCheckOverlap);

    auto& thirdTransportSolenoid = thirdTransportField.NewDaughter<Detector::Geometry::Fast::ThirdTransportSolenoid>(fCheckOverlap);

    // 3

    auto& cdcGas = cdcBody.NewDaughter<Detector::Geometry::Fast::CDCGas>(fCheckOverlap);

    auto& beamDegrader = linacField.NewDaughter<Detector::Geometry::Fast::BeamDegrader>(fCheckOverlap);
    auto& beamMonitor = linacField.NewDaughter<Detector::Geometry::Fast::BeamMonitor>(fCheckOverlap);
    auto& target = linacField.NewDaughter<Detector::Geometry::Fast::Target>(fCheckOverlap);

    // 4

    auto& cdcSuperLayer = cdcGas.NewDaughter<Detector::Geometry::Fast::CDCSuperLayer>(fCheckOverlap);

    // 5

    auto& cdcSenseLayer = cdcSuperLayer.NewDaughter<Detector::Geometry::Fast::CDCSenseLayer>(fCheckOverlap);

    // 6

    auto& cdcFieldWire = cdcSenseLayer.NewDaughter<Detector::Geometry::Fast::CDCFieldWire>(fCheckOverlap);
    auto& cdcCell = cdcSenseLayer.NewDaughter<Detector::Geometry::Fast::CDCCell>(fCheckOverlap);

    // 7

    auto& cdcSenseWire = cdcCell.NewDaughter<Detector::Geometry::Fast::CDCSenseWire>(fCheckOverlap);

    ////////////////////////////////////////////////////////////////
    // Register materials
    ////////////////////////////////////////////////////////////////
    {
        using namespace MACE::LiteralUnit::Density;

        const auto nist = G4NistManager::Instance();

        const auto aluminium = nist->FindOrBuildMaterial("G4_Al");
        beamDegrader.RegisterMaterial(aluminium);
        cdcFieldWire.RegisterMaterial(aluminium);

        const auto cdcHeBasedGas = [&nist] {
            constexpr auto heFraction = 0.85;
            constexpr auto butaneFraction = 1 - heFraction;
            const auto he = nist->FindOrBuildMaterial("G4_He");
            const auto butane = nist->FindOrBuildMaterial("G4_BUTANE");
            const auto gas = new G4Material("CDCGas",
                                            heFraction * he->GetDensity() +
                                                butaneFraction * butane->GetDensity(),
                                            2,
                                            kStateGas);
            gas->AddMaterial(he, heFraction);
            gas->AddMaterial(butane, butaneFraction);
            return gas;
        }();
        cdcCell.RegisterMaterial(cdcHeBasedGas);
        cdcGas.RegisterMaterial(cdcHeBasedGas);
        cdcSenseLayer.RegisterMaterial(cdcHeBasedGas);
        cdcSuperLayer.RegisterMaterial(cdcHeBasedGas);

        const auto cdcShell = nist->BuildMaterialWithNewDensity("CarbonFiber", "G4_C", 1.7_g_cm3);
        cdcBody.RegisterMaterial(cdcShell);

        const auto copper = nist->FindOrBuildMaterial("G4_Cu");
        collimator.RegisterMaterial(copper);
        firstBendSolenoid.RegisterMaterial(copper);
        firstTransportSolenoid.RegisterMaterial(copper);
        secondBendSolenoid.RegisterMaterial(copper);
        secondTransportSolenoid.RegisterMaterial(copper);
        thirdTransportSolenoid.RegisterMaterial(copper);

        const auto csI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
        emCal.RegisterMaterial(csI);

        const auto iron = nist->FindOrBuildMaterial("G4_Fe");
        spectrometerMagnet.RegisterMaterial(iron);

        const auto lead = nist->FindOrBuildMaterial("G4_Pb");
        emCalShield.RegisterMaterial(lead);
        spectrometerShield.RegisterMaterial(lead);

        const auto mcpMaterial = nist->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4_g_cm3);
        mcp.RegisterMaterial(mcpMaterial);

        const auto plasticScitillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
        beamMonitor.RegisterMaterial(plasticScitillator);

        const auto silicaAerogel = nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30_mg_cm3);
        target.RegisterMaterial(silicaAerogel);

        const auto tungsten = nist->FindOrBuildMaterial("G4_W");
        cdcSenseWire.RegisterMaterial(tungsten);

        const auto vacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3);
        emCalField.RegisterMaterial(vacuum);
        firstBendField.RegisterMaterial(vacuum);
        firstTransportField.RegisterMaterial(vacuum);
        linacField.RegisterMaterial(vacuum);
        secondBendField.RegisterMaterial(vacuum);
        secondTransportField.RegisterMaterial(vacuum);
        selectorField.RegisterMaterial(vacuum);
        spectrometerField.RegisterMaterial(vacuum);
        thirdTransportField.RegisterMaterial(vacuum);
        fWorld->RegisterMaterial(vacuum);
    }

    ////////////////////////////////////////////////////////////////
    // Register regions
    ////////////////////////////////////////////////////////////////
    {
        const auto defaultCuts = G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts();

        // CDCFieldWireRegion
        fCDCFieldWireRegion = new Region("CDCFieldWire", RegionType::CDCFieldWire);
        fCDCFieldWireRegion->SetProductionCuts(defaultCuts);

        cdcFieldWire.RegisterRegion(fCDCFieldWireRegion);

        // CDCSenseWireRegion
        fCDCSenseWireRegion = new Region("CDCSenseWire", RegionType::CDCSenseWire);
        fCDCSenseWireRegion->SetProductionCuts(defaultCuts);

        cdcSenseWire.RegisterRegion(fCDCSenseWireRegion);

        // DefaultGaseousRegion
        fDefaultGaseousRegion = new Region("DefaultGaseous", RegionType::DefaultGaseous);
        fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion(fDefaultGaseousRegion);
        cdcGas.RegisterRegion(fDefaultGaseousRegion);
        cdcSuperLayer.RegisterRegion(fDefaultGaseousRegion);

        // DefaultSolidRegion
        fDefaultSolidRegion = new Region("DefaultSolid", RegionType::DefaultSolid);
        fDefaultSolidRegion->SetProductionCuts(defaultCuts);

        beamDegrader.RegisterRegion(fDefaultSolidRegion);
        beamMonitor.RegisterRegion(fDefaultSolidRegion);
        cdcBody.RegisterRegion(fDefaultSolidRegion);
        collimator.RegisterRegion(fDefaultSolidRegion);

        // EMCalSensitiveRegion
        fEMCalSensitiveRegion = new Region("EMCalSensitive", RegionType::EMCalSensitive);
        fEMCalSensitiveRegion->SetProductionCuts(defaultCuts);

        emCal.RegisterRegion(fEMCalSensitiveRegion);

        // MCPSensitiveRegion
        fMCPSensitiveRegion = new Region("MCPSensitive", RegionType::MCPSensitive);
        fMCPSensitiveRegion->SetProductionCuts(defaultCuts);

        mcp.RegisterRegion(fMCPSensitiveRegion);

        // ShieldRegion
        fShieldRegion = new Region("Shield", RegionType::Shield);
        fShieldRegion->SetProductionCuts(defaultCuts);

        emCalShield.RegisterRegion(fShieldRegion);
        spectrometerShield.RegisterRegion(fShieldRegion);

        // SolenoidOrMagnetRegion
        fSolenoidOrMagnetRegion = new Region("SolenoidOrMagnet", RegionType::SolenoidOrMagnet);
        fSolenoidOrMagnetRegion->SetProductionCuts(defaultCuts);

        firstBendSolenoid.RegisterRegion(fSolenoidOrMagnetRegion);
        firstTransportSolenoid.RegisterRegion(fSolenoidOrMagnetRegion);
        secondBendSolenoid.RegisterRegion(fSolenoidOrMagnetRegion);
        secondTransportSolenoid.RegisterRegion(fSolenoidOrMagnetRegion);
        spectrometerMagnet.RegisterRegion(fSolenoidOrMagnetRegion);
        thirdTransportSolenoid.RegisterRegion(fSolenoidOrMagnetRegion);

        // SpectrometerSensitiveRegion
        fSpectrometerSensitiveRegion = new Region("SpectrometerSensitive", RegionType::SpectrometerSensitive);
        fSpectrometerSensitiveRegion->SetProductionCuts(defaultCuts);

        // TargetRegion
        fTargetRegion = new Region("Target", RegionType::Target);
        fTargetRegion->SetProductionCuts(defaultCuts);

        target.RegisterRegion(fTargetRegion);

        // VacuumRegion
        fVacuumRegion = new Region("Vacuum", RegionType::Vacuum);
        fVacuumRegion->SetProductionCuts(defaultCuts);

        emCalField.RegisterRegion(fVacuumRegion);
        firstBendField.RegisterRegion(fVacuumRegion);
        firstTransportField.RegisterRegion(fVacuumRegion);
        linacField.RegisterRegion(fVacuumRegion);
        secondBendField.RegisterRegion(fVacuumRegion);
        secondTransportField.RegisterRegion(fVacuumRegion);
        selectorField.RegisterRegion(fVacuumRegion);
        spectrometerField.RegisterRegion(fVacuumRegion);
        thirdTransportField.RegisterRegion(fVacuumRegion);
    }

    ////////////////////////////////////////////////////////////////
    // Register SDs
    ////////////////////////////////////////////////////////////////
    {
        fCDCSD = new CDCSD(cdcCell.LogicalVolume()->GetName());
        cdcCell.RegisterSD(fCDCSD);

        fEMCalSD = new EMCalSD(emCal.LogicalVolume()->GetName());
        emCal.RegisterSD(fEMCalSD);

        fMCPSD = new MCPSD(mcp.LogicalVolume()->GetName());
        mcp.RegisterSD(fMCPSD);
    }

    ////////////////////////////////////////////////////////////////
    // Register background fields
    ////////////////////////////////////////////////////////////////
    {
        using namespace MACE::LiteralUnit::Length;
        using namespace MACE::LiteralUnit::MagneticFluxDensity;

        constexpr auto hMin = 50_um;

        constexpr auto defaultB = 0.1_T;
        const auto parallelBField = new ParallelField(defaultB);
        const auto verticalBField = new VerticalField(defaultB);

        spectrometerField.RegisterField<
            ParallelField,
            G4TMagFieldEquation<ParallelField>,
            G4TDormandPrince45<G4TMagFieldEquation<ParallelField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<ParallelField>>>>(
            parallelBField, hMin, 6, 6, true);

        linacField.RegisterField<
            LinacField,
            G4EqMagElectricField,
            G4TDormandPrince45<G4EqMagElectricField, 8>,
            G4InterpolationDriver<G4TDormandPrince45<G4EqMagElectricField, 8>>>(
            new LinacField, hMin, 8, 8, false);

        firstTransportField.RegisterField<
            ParallelField,
            G4TMagFieldEquation<ParallelField>,
            G4TDormandPrince45<G4TMagFieldEquation<ParallelField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<ParallelField>>>>(
            parallelBField, hMin, 6, 6, true);

        firstBendField.RegisterField<
            FirstBendField,
            G4TMagFieldEquation<FirstBendField>,
            G4TDormandPrince45<G4TMagFieldEquation<FirstBendField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<FirstBendField>>>>(
            new FirstBendField, hMin, 6, 6, true);

        secondTransportField.RegisterField<
            VerticalField,
            G4TMagFieldEquation<VerticalField>,
            G4TDormandPrince45<G4TMagFieldEquation<VerticalField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<VerticalField>>>>(
            verticalBField, hMin, 6, 6, true);

        selectorField.RegisterField<
            SelectorField,
            G4EqMagElectricField,
            G4TDormandPrince45<G4EqMagElectricField, 8>,
            G4InterpolationDriver<G4TDormandPrince45<G4EqMagElectricField, 8>>>(
            new SelectorField, hMin, 8, 8, true);

        secondBendField.RegisterField<
            SecondBendField,
            G4TMagFieldEquation<SecondBendField>,
            G4TDormandPrince45<G4TMagFieldEquation<SecondBendField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<SecondBendField>>>>(
            new SecondBendField, hMin, 6, 6, true);

        thirdTransportField.RegisterField<
            ParallelField,
            G4TMagFieldEquation<ParallelField>,
            G4TDormandPrince45<G4TMagFieldEquation<ParallelField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<ParallelField>>>>(
            parallelBField, hMin, 6, 6, true);

        emCalField.RegisterField<
            ParallelField,
            G4TMagFieldEquation<ParallelField>,
            G4TDormandPrince45<G4TMagFieldEquation<ParallelField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<ParallelField>>>>(
            parallelBField, hMin, 6, 6, true);
    }

    return fWorld->PhysicalVolume().get();
}

} // namespace MACE::SimMACE::inline Action
