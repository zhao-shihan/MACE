#include "MACE/Detector/Field/G4/AcceleratorField.h++"
#include "MACE/Detector/Field/G4/EMCField.h++"
#include "MACE/Detector/Field/G4/SolenoidB1Field.h++"
#include "MACE/Detector/Field/G4/SolenoidB2Field.h++"
#include "MACE/Detector/Field/G4/SolenoidS1Field.h++"
#include "MACE/Detector/Field/G4/SolenoidS2Field.h++"
#include "MACE/Detector/Field/G4/SolenoidS3Field.h++"
#include "MACE/Detector/Field/G4/SpectrometerField.h++"
#include "MACE/Detector/Geometry/Fast/AcceleratorField.h++"
#include "MACE/Detector/Geometry/Fast/BeamDegrader.h++"
#include "MACE/Detector/Geometry/Fast/BeamMonitor.h++"
#include "MACE/Detector/Geometry/Fast/CDCBody.h++"
#include "MACE/Detector/Geometry/Fast/CDCCell.h++"
#include "MACE/Detector/Geometry/Fast/CDCFieldWire.h++"
#include "MACE/Detector/Geometry/Fast/CDCGas.h++"
#include "MACE/Detector/Geometry/Fast/CDCSenseLayer.h++"
#include "MACE/Detector/Geometry/Fast/CDCSenseWire.h++"
#include "MACE/Detector/Geometry/Fast/CDCSuperLayer.h++"
#include "MACE/Detector/Geometry/Fast/EMCCrystal.h++"
#include "MACE/Detector/Geometry/Fast/EMCField.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTCathode.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTCoupler.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTWindow.h++"
#include "MACE/Detector/Geometry/Fast/EMCShield.h++"
#include "MACE/Detector/Geometry/Fast/Filter.h++"
#include "MACE/Detector/Geometry/Fast/MCP.h++"
#include "MACE/Detector/Geometry/Fast/ShieldingWall.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB1.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB1Field.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB2.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB2Field.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS1.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS1Field.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS2.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS2Field.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS3.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS3Field.h++"
#include "MACE/Detector/Geometry/Fast/SpectrometerField.h++"
#include "MACE/Detector/Geometry/Fast/SpectrometerMagnet.h++"
#include "MACE/Detector/Geometry/Fast/SpectrometerShield.h++"
#include "MACE/Detector/Geometry/Fast/Target.h++"
#include "MACE/Detector/Geometry/Fast/World.h++"
#include "MACE/Detector/Geometry/GeometryBase.h++"
#include "MACE/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/SimMACE/Messenger/DetectorMessenger.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4EqMagElectricField.hh"
#include "G4InterpolationDriver.hh"
#include "G4NistManager.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

namespace MACE::SimMACE::inline Action {

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{},
    fWorld{std::make_shared<Detector::Geometry::Fast::World>()},
    fCDCFieldWireRegion{},
    fCDCSenseWireRegion{},
    fDefaultGaseousRegion{},
    fDefaultSolidRegion{},
    fEMCSensitiveRegion{},
    fMCPSensitiveRegion{},
    fShieldRegion{},
    fSolenoidOrMagnetRegion{},
    fSpectrometerSensitiveRegion{},
    fTargetRegion{},
    fVacuumRegion{},
    fCDCSD{},
    fEMCSD{},
    fMCPSD{} {
    /*     Detector::Description::DescriptionIO::Import<DescriptionInUse>(
    #include "MACE/SimMACE/DefaultGeometry.inlyaml"
        ); */
    DetectorMessenger::EnsureInstantiated();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    // 1

    auto& emcField = fWorld->NewDaughter<Detector::Geometry::Fast::EMCField>(fCheckOverlap);
    auto& emcShield = fWorld->NewDaughter<Detector::Geometry::Fast::EMCShield>(fCheckOverlap);
    auto& solenoidB1Field = fWorld->NewDaughter<Detector::Geometry::Fast::SolenoidB1Field>(fCheckOverlap);
    auto& solenoidB2Field = fWorld->NewDaughter<Detector::Geometry::Fast::SolenoidB2Field>(fCheckOverlap);
    auto& solenoidS1Field = fWorld->NewDaughter<Detector::Geometry::Fast::SolenoidS1Field>(fCheckOverlap);
    auto& solenoidS2Field = fWorld->NewDaughter<Detector::Geometry::Fast::SolenoidS2Field>(fCheckOverlap);
    auto& solenoidS3Field = fWorld->NewDaughter<Detector::Geometry::Fast::SolenoidS3Field>(fCheckOverlap);
    auto& spectrometerField = fWorld->NewDaughter<Detector::Geometry::Fast::SpectrometerField>(fCheckOverlap);
    auto& spectrometerShield = fWorld->NewDaughter<Detector::Geometry::Fast::SpectrometerShield>(fCheckOverlap);
    auto& shieldingWall = fWorld->NewDaughter<Detector::Geometry::Fast::ShieldingWall>(fCheckOverlap);

    // 2

    auto& emcCrystal = emcField.NewDaughter<Detector::Geometry::Fast::EMCCrystal>(fCheckOverlap);
    auto& emcPMTCoupler = emcField.NewDaughter<Detector::Geometry::Fast::EMCPMTCoupler>(fCheckOverlap);
    auto& emcPMTWindow = emcField.NewDaughter<Detector::Geometry::Fast::EMCPMTWindow>(fCheckOverlap);
    auto& emcPMTCathode = emcField.NewDaughter<Detector::Geometry::Fast::EMCPMTCathode>(fCheckOverlap);

    auto& mcp = emcField.NewDaughter<Detector::Geometry::Fast::MCP>(fCheckOverlap);

    auto& solenoidB1 = solenoidB1Field.NewDaughter<Detector::Geometry::Fast::SolenoidB1>(fCheckOverlap);

    auto& solenoidS1 = solenoidS1Field.NewDaughter<Detector::Geometry::Fast::SolenoidS1>(fCheckOverlap);

    auto& solenoidB2 = solenoidB2Field.NewDaughter<Detector::Geometry::Fast::SolenoidB2>(fCheckOverlap);

    auto& filter = solenoidS2Field.NewDaughter<Detector::Geometry::Fast::Filter>(fCheckOverlap);
    auto& solenoidS2 = solenoidS2Field.NewDaughter<Detector::Geometry::Fast::SolenoidS2>(fCheckOverlap);

    auto& acceleratorField = spectrometerField.NewDaughter<Detector::Geometry::Fast::AcceleratorField>(fCheckOverlap);
    auto& cdcBody = spectrometerField.NewDaughter<Detector::Geometry::Fast::CDCBody>(fCheckOverlap);
    auto& spectrometerMagnet = spectrometerField.NewDaughter<Detector::Geometry::Fast::SpectrometerMagnet>(fCheckOverlap);

    auto& solenoidS3 = solenoidS3Field.NewDaughter<Detector::Geometry::Fast::SolenoidS3>(fCheckOverlap);

    // 3

    auto& cdcGas = cdcBody.NewDaughter<Detector::Geometry::Fast::CDCGas>(fCheckOverlap);

    auto& beamDegrader = acceleratorField.NewDaughter<Detector::Geometry::Fast::BeamDegrader>(fCheckOverlap);
    auto& beamMonitor = acceleratorField.NewDaughter<Detector::Geometry::Fast::BeamMonitor>(fCheckOverlap);
    auto& target = acceleratorField.NewDaughter<Detector::Geometry::Fast::Target>(fCheckOverlap);

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
        solenoidB1.RegisterMaterial(copper);
        solenoidS1.RegisterMaterial(copper);
        solenoidB2.RegisterMaterial(copper);
        solenoidS2.RegisterMaterial(copper);
        solenoidS3.RegisterMaterial(copper);
        filter.RegisterMaterial(copper);

        // const auto csI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
        // emc.RegisterMaterial(csI);

        const auto iron = nist->FindOrBuildMaterial("G4_Fe");
        spectrometerMagnet.RegisterMaterial(iron);

        const auto lead = nist->FindOrBuildMaterial("G4_Pb");
        emcShield.RegisterMaterial(lead);
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
        emcField.RegisterMaterial(vacuum);
        solenoidB1Field.RegisterMaterial(vacuum);
        solenoidS1Field.RegisterMaterial(vacuum);
        acceleratorField.RegisterMaterial(vacuum);
        solenoidB2Field.RegisterMaterial(vacuum);
        solenoidS2Field.RegisterMaterial(vacuum);
        spectrometerField.RegisterMaterial(vacuum);
        solenoidS3Field.RegisterMaterial(vacuum);
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
        filter.RegisterRegion(fDefaultSolidRegion);
        shieldingWall.RegisterRegion(fDefaultSolidRegion);

        // EMCSensitiveRegion
        fEMCSensitiveRegion = new Region("EMCSensitive", RegionType::EMCSensitive);
        fEMCSensitiveRegion->SetProductionCuts(defaultCuts);

        emcCrystal.RegisterRegion(fEMCSensitiveRegion);
        emcPMTCoupler.RegisterRegion(fEMCSensitiveRegion);
        emcPMTWindow.RegisterRegion(fEMCSensitiveRegion);
        emcPMTCathode.RegisterRegion(fEMCSensitiveRegion);

        // MCPSensitiveRegion
        fMCPSensitiveRegion = new Region("MCPSensitive", RegionType::MCPSensitive);
        fMCPSensitiveRegion->SetProductionCuts(defaultCuts);

        mcp.RegisterRegion(fMCPSensitiveRegion);

        // ShieldRegion
        fShieldRegion = new Region("Shield", RegionType::Shield);
        fShieldRegion->SetProductionCuts(defaultCuts);

        emcShield.RegisterRegion(fShieldRegion);
        spectrometerShield.RegisterRegion(fShieldRegion);

        // SolenoidOrMagnetRegion
        fSolenoidOrMagnetRegion = new Region("SolenoidOrMagnet", RegionType::SolenoidOrMagnet);
        fSolenoidOrMagnetRegion->SetProductionCuts(defaultCuts);

        solenoidB1.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS1.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidB2.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS2.RegisterRegion(fSolenoidOrMagnetRegion);
        spectrometerMagnet.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS3.RegisterRegion(fSolenoidOrMagnetRegion);

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

        emcField.RegisterRegion(fVacuumRegion);
        solenoidB1Field.RegisterRegion(fVacuumRegion);
        solenoidS1Field.RegisterRegion(fVacuumRegion);
        acceleratorField.RegisterRegion(fVacuumRegion);
        solenoidB2Field.RegisterRegion(fVacuumRegion);
        solenoidS2Field.RegisterRegion(fVacuumRegion);
        spectrometerField.RegisterRegion(fVacuumRegion);
        solenoidS3Field.RegisterRegion(fVacuumRegion);
    }

    ////////////////////////////////////////////////////////////////
    // Register SDs
    ////////////////////////////////////////////////////////////////
    {
        fCDCSD = new SD::CDCSD(cdcCell.LogicalVolume()->GetName());
        cdcCell.RegisterSD(fCDCSD);

        fEMCSD = new SD::EMCSD(emcCrystal.LogicalVolume()->GetName());
        emcCrystal.RegisterSD(fEMCSD);

        fMCPSD = new SD::MCPSD(mcp.LogicalVolume()->GetName());
        mcp.RegisterSD(fMCPSD);
    }

    ////////////////////////////////////////////////////////////////
    // Register background fields
    ////////////////////////////////////////////////////////////////
    {
        using namespace LiteralUnit::Length;
        using namespace LiteralUnit::MagneticFluxDensity;
        using namespace Detector::Field::G4;

        constexpr auto hMin = 50_um;

        spectrometerField.RegisterField<
            SpectrometerField,
            G4TMagFieldEquation<SpectrometerField>,
            G4TDormandPrince45<G4TMagFieldEquation<SpectrometerField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<SpectrometerField>>>>(
            new SpectrometerField, hMin, 6, 6, false);

        acceleratorField.RegisterField<
            AcceleratorField,
            G4EqMagElectricField,
            G4TDormandPrince45<G4EqMagElectricField, 8>,
            G4InterpolationDriver<G4TDormandPrince45<G4EqMagElectricField, 8>>>(
            new AcceleratorField, hMin, 8, 8, false);

        solenoidS1Field.RegisterField<
            SolenoidS1Field,
            G4TMagFieldEquation<SolenoidS1Field>,
            G4TDormandPrince45<G4TMagFieldEquation<SolenoidS1Field>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<SolenoidS1Field>>>>(
            new SolenoidS1Field, hMin, 6, 6, false);

        solenoidB1Field.RegisterField<
            SolenoidB1Field,
            G4TMagFieldEquation<SolenoidB1Field>,
            G4TDormandPrince45<G4TMagFieldEquation<SolenoidB1Field>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<SolenoidB1Field>>>>(
            new SolenoidB1Field, hMin, 6, 6, false);

        solenoidS2Field.RegisterField<
            SolenoidS2Field,
            G4TMagFieldEquation<SolenoidS2Field>,
            G4TDormandPrince45<G4TMagFieldEquation<SolenoidS2Field>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<SolenoidS2Field>>>>(
            new SolenoidS2Field, hMin, 6, 6, false);

        solenoidB2Field.RegisterField<
            SolenoidB2Field,
            G4TMagFieldEquation<SolenoidB2Field>,
            G4TDormandPrince45<G4TMagFieldEquation<SolenoidB2Field>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<SolenoidB2Field>>>>(
            new SolenoidB2Field, hMin, 6, 6, false);

        solenoidS3Field.RegisterField<
            SolenoidS3Field,
            G4TMagFieldEquation<SolenoidS3Field>,
            G4TDormandPrince45<G4TMagFieldEquation<SolenoidS3Field>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<SolenoidS3Field>>>>(
            new SolenoidS3Field, hMin, 6, 6, false);

        emcField.RegisterField<
            EMCField,
            G4TMagFieldEquation<EMCField>,
            G4TDormandPrince45<G4TMagFieldEquation<EMCField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<EMCField>>>>(
            new EMCField, hMin, 6, 6, false);
    }

    return fWorld->PhysicalVolume().get();
}

} // namespace MACE::SimMACE::inline Action
