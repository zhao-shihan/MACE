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

namespace MACE::SimMACE::Action {

DetectorConstruction::DetectorConstruction() :
    NonMoveableBase(),
    G4VUserDetectorConstruction(),
    fCheckOverlap(false),
    fWorld(std::make_shared<Core::Geometry::Entity::Fast::World>()),
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
    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    using namespace Core::Geometry::Entity::Fast;

    // 1

    auto& emCalField = fWorld->NewDaughter<EMCalField>(fCheckOverlap);
    auto& emCalShield = fWorld->NewDaughter<EMCalShield>(fCheckOverlap);
    auto& firstBendField = fWorld->NewDaughter<FirstBendField>(fCheckOverlap);
    auto& firstTransportField = fWorld->NewDaughter<FirstTransportField>(fCheckOverlap);
    auto& secondBendField = fWorld->NewDaughter<SecondBendField>(fCheckOverlap);
    auto& secondTransportField = fWorld->NewDaughter<SecondTransportField>(fCheckOverlap);
    auto& spectrometerField = fWorld->NewDaughter<SpectrometerField>(fCheckOverlap);
    auto& spectrometerShield = fWorld->NewDaughter<SpectrometerShield>(fCheckOverlap);
    auto& thirdTransportField = fWorld->NewDaughter<ThirdTransportField>(fCheckOverlap);

    // 2

    auto& emCal = emCalField.NewDaughter<EMCal>(fCheckOverlap);
    auto& mcp = emCalField.NewDaughter<MCP>(fCheckOverlap);

    auto& firstBendSolenoid = firstBendField.NewDaughter<FirstBendSolenoid>(fCheckOverlap);

    auto& firstTransportSolenoid = firstTransportField.NewDaughter<FirstTransportSolenoid>(fCheckOverlap);

    auto& secondBendSolenoid = secondBendField.NewDaughter<SecondBendSolenoid>(fCheckOverlap);

    auto& collimator = secondTransportField.NewDaughter<Collimator>(fCheckOverlap);
    auto& secondTransportSolenoid = secondTransportField.NewDaughter<SecondTransportSolenoid>(fCheckOverlap);
    auto& selectorField = secondTransportField.NewDaughter<SelectorField>(fCheckOverlap);

    auto& cdcBody = spectrometerField.NewDaughter<CDCBody>(fCheckOverlap);
    auto& linacField = spectrometerField.NewDaughter<LinacField>(fCheckOverlap);
    auto& spectrometerMagnet = spectrometerField.NewDaughter<SpectrometerMagnet>(fCheckOverlap);

    auto& thirdTransportSolenoid = thirdTransportField.NewDaughter<ThirdTransportSolenoid>(fCheckOverlap);

    // 3

    auto& cdcGas = cdcBody.NewDaughter<CDCGas>(fCheckOverlap);

    auto& beamDegrader = linacField.NewDaughter<BeamDegrader>(fCheckOverlap);
    auto& beamMonitor = linacField.NewDaughter<BeamMonitor>(fCheckOverlap);
    auto& target = linacField.NewDaughter<Target>(fCheckOverlap);

    // 4

    auto& cdcSuperLayer = cdcGas.NewDaughter<CDCSuperLayer>(fCheckOverlap);

    // 5

    auto& cdcSenseLayer = cdcSuperLayer.NewDaughter<CDCSenseLayer>(fCheckOverlap);

    // 6

    auto& cdcFieldWire = cdcSenseLayer.NewDaughter<CDCFieldWire>(fCheckOverlap);
    auto& cdcCell = cdcSenseLayer.NewDaughter<CDCCell>(fCheckOverlap);

    // 7

    auto& cdcSenseWire = cdcCell.NewDaughter<CDCSenseWire>(fCheckOverlap);

    ////////////////////////////////////////////////////////////////
    // Register materials
    ////////////////////////////////////////////////////////////////
    {
        using namespace MACE::Utility::LiteralUnit::Density;

        const auto nist = G4NistManager::Instance();

        const auto aluminium = nist->FindOrBuildMaterial("G4_Al");
        beamDegrader.RegisterMaterial(aluminium);
        cdcFieldWire.RegisterMaterial(aluminium);

        const auto he = nist->FindOrBuildMaterial("G4_He");
        cdcCell.RegisterMaterial(he);
        cdcGas.RegisterMaterial(he);
        cdcSenseLayer.RegisterMaterial(he);
        cdcSuperLayer.RegisterMaterial(he);

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

        // EMCalSensitiveRegion
        fEMCalSensitiveRegion = new Region("EMCalSensitive", RegionType::EMCalSensitive);
        fEMCalSensitiveRegion->SetProductionCuts(defaultCuts);

        emCal.RegisterRegion(fEMCalSensitiveRegion);

        // DefaultSolidRegion
        fDefaultSolidRegion = new Region("DefaultSolid", RegionType::DefaultSolid);
        fDefaultSolidRegion->SetProductionCuts(defaultCuts);

        beamDegrader.RegisterRegion(fDefaultSolidRegion);
        beamMonitor.RegisterRegion(fDefaultSolidRegion);
        cdcBody.RegisterRegion(fDefaultSolidRegion);
        cdcFieldWire.RegisterRegion(fDefaultSolidRegion);
        cdcSenseWire.RegisterRegion(fDefaultSolidRegion);
        collimator.RegisterRegion(fDefaultSolidRegion);

        // DefaultGaseousRegion
        fDefaultGaseousRegion = new Region("DefaultGaseous", RegionType::DefaultGaseous);
        fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion(fDefaultGaseousRegion);
        cdcGas.RegisterRegion(fDefaultGaseousRegion);
        cdcSuperLayer.RegisterRegion(fDefaultGaseousRegion);

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

        // MCPSensitiveRegion
        fMCPSensitiveRegion = new Region("MCPSensitive", RegionType::MCPSensitive);
        fMCPSensitiveRegion->SetProductionCuts(defaultCuts);

        mcp.RegisterRegion(fMCPSensitiveRegion);
    }

    ////////////////////////////////////////////////////////////////
    // Register SDs
    ////////////////////////////////////////////////////////////////
    {
        fCDCSD = new SD::CDCSD(cdcCell.LogicalVolume()->GetName());
        cdcCell.RegisterSD(fCDCSD);

        fEMCalSD = new SD::EMCalSD(emCal.LogicalVolume()->GetName());
        emCal.RegisterSD(fEMCalSD);

        fMCPSD = new SD::MCPSD(mcp.LogicalVolume()->GetName());
        mcp.RegisterSD(fMCPSD);
    }

    ////////////////////////////////////////////////////////////////
    // Register background fields
    ////////////////////////////////////////////////////////////////
    {
        using namespace MACE::Utility::LiteralUnit::Length;
        using namespace MACE::Utility::LiteralUnit::MagneticFluxDensity;
        using namespace Field;

        constexpr auto hMin = 1_um;

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

} // namespace MACE::SimMACE::Action
