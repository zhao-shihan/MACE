#include "MACE/Detector/Definition/AcceleratorField.h++"
#include "MACE/Detector/Definition/BeamDegrader.h++"
#include "MACE/Detector/Definition/BeamMonitor.h++"
#include "MACE/Detector/Definition/CDCBody.h++"
#include "MACE/Detector/Definition/CDCCell.h++"
#include "MACE/Detector/Definition/CDCGas.h++"
#include "MACE/Detector/Definition/CDCSenseLayer.h++"
#include "MACE/Detector/Definition/CDCSuperLayer.h++"
#include "MACE/Detector/Definition/DefinitionBase.h++"
#include "MACE/Detector/Definition/EMCCrystal.h++"
#include "MACE/Detector/Definition/EMCField.h++"
#include "MACE/Detector/Definition/EMCMagnet.h++"
#include "MACE/Detector/Definition/EMCPMTAssemblies.h++"
#include "MACE/Detector/Definition/EMCShield.h++"
#include "MACE/Detector/Definition/Filter.h++"
#include "MACE/Detector/Definition/MCP.h++"
#include "MACE/Detector/Definition/ShieldingWall.h++"
#include "MACE/Detector/Definition/SolenoidB1.h++"
#include "MACE/Detector/Definition/SolenoidB1Field.h++"
#include "MACE/Detector/Definition/SolenoidB2.h++"
#include "MACE/Detector/Definition/SolenoidB2Field.h++"
#include "MACE/Detector/Definition/SolenoidS1.h++"
#include "MACE/Detector/Definition/SolenoidS1Field.h++"
#include "MACE/Detector/Definition/SolenoidS2.h++"
#include "MACE/Detector/Definition/SolenoidS2Field.h++"
#include "MACE/Detector/Definition/SolenoidS3.h++"
#include "MACE/Detector/Definition/SolenoidS3Field.h++"
#include "MACE/Detector/Definition/SpectrometerField.h++"
#include "MACE/Detector/Definition/SpectrometerMagnet.h++"
#include "MACE/Detector/Definition/SpectrometerShield.h++"
#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/SimMACE/Messenger/DetectorMessenger.h++"
#include "MACE/Simulation/Field/AcceleratorField.h++"
#include "MACE/Simulation/Field/EMCField.h++"
#include "MACE/Simulation/Field/SolenoidB1Field.h++"
#include "MACE/Simulation/Field/SolenoidB2Field.h++"
#include "MACE/Simulation/Field/SolenoidS1Field.h++"
#include "MACE/Simulation/Field/SolenoidS2Field.h++"
#include "MACE/Simulation/Field/SolenoidS3Field.h++"
#include "MACE/Simulation/Field/SpectrometerField.h++"
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
    fWorld{},
    fCDCFieldWireRegion{},
    fCDCSenseWireRegion{},
    fDefaultGaseousRegion{},
    fDefaultSolidRegion{},
    fEMCSensitiveRegion{},
    fMCPSensitiveRegion{},
    fShieldRegion{},
    fSolenoidOrMagnetRegion{},
    fCDCSensitiveRegion{},
    fTargetRegion{},
    fVacuumRegion{},
    fCDCSD{},
    fEMCSD{},
    fMCPSD{} {
    /*     Detector::Description::DescriptionIO::Import<DescriptionInUse>(
    #include "MACE/SimMACE/DefaultGeometry.inlyaml"
        ); */
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    // 0

    fWorld = std::make_unique<Detector::Definition::World>();

    // 1

    auto& emcField = fWorld->NewDaughter<Detector::Definition::EMCField>(fCheckOverlap);
    auto& emcShield = fWorld->NewDaughter<Detector::Definition::EMCShield>(fCheckOverlap);
    auto& solenoidB1Field = fWorld->NewDaughter<Detector::Definition::SolenoidB1Field>(fCheckOverlap);
    auto& solenoidB2Field = fWorld->NewDaughter<Detector::Definition::SolenoidB2Field>(fCheckOverlap);
    auto& solenoidS1Field = fWorld->NewDaughter<Detector::Definition::SolenoidS1Field>(fCheckOverlap);
    auto& solenoidS2Field = fWorld->NewDaughter<Detector::Definition::SolenoidS2Field>(fCheckOverlap);
    auto& solenoidS3Field = fWorld->NewDaughter<Detector::Definition::SolenoidS3Field>(fCheckOverlap);
    auto& spectrometerField = fWorld->NewDaughter<Detector::Definition::SpectrometerField>(fCheckOverlap);
    auto& spectrometerShield = fWorld->NewDaughter<Detector::Definition::SpectrometerShield>(fCheckOverlap);
    auto& shieldingWall = fWorld->NewDaughter<Detector::Definition::ShieldingWall>(fCheckOverlap);

    // 2

    auto& emcCrystal = emcField.NewDaughter<Detector::Definition::EMCCrystal>(fCheckOverlap);
    auto& emcPMTAssemblies = emcField.NewDaughter<Detector::Definition::EMCPMTAssemblies>(fCheckOverlap);
    auto& emcMagnet = emcField.NewDaughter<Detector::Definition::EMCMagnet>(fCheckOverlap);

    auto& mcp = emcField.NewDaughter<Detector::Definition::MCP>(fCheckOverlap);

    auto& solenoidB1 = solenoidB1Field.NewDaughter<Detector::Definition::SolenoidB1>(fCheckOverlap);

    auto& solenoidS1 = solenoidS1Field.NewDaughter<Detector::Definition::SolenoidS1>(fCheckOverlap);

    auto& solenoidB2 = solenoidB2Field.NewDaughter<Detector::Definition::SolenoidB2>(fCheckOverlap);

    auto& filter = solenoidS2Field.NewDaughter<Detector::Definition::Filter>(fCheckOverlap);
    auto& solenoidS2 = solenoidS2Field.NewDaughter<Detector::Definition::SolenoidS2>(fCheckOverlap);

    auto& acceleratorField = spectrometerField.NewDaughter<Detector::Definition::AcceleratorField>(fCheckOverlap);
    auto& cdcBody = spectrometerField.NewDaughter<Detector::Definition::CDCBody>(fCheckOverlap);
    auto& spectrometerMagnet = spectrometerField.NewDaughter<Detector::Definition::SpectrometerMagnet>(fCheckOverlap);

    auto& solenoidS3 = solenoidS3Field.NewDaughter<Detector::Definition::SolenoidS3>(fCheckOverlap);

    // 3

    auto& cdcGas = cdcBody.NewDaughter<Detector::Definition::CDCGas>(fCheckOverlap);

    auto& beamDegrader = acceleratorField.NewDaughter<Detector::Definition::BeamDegrader>(fCheckOverlap);
    auto& beamMonitor = acceleratorField.NewDaughter<Detector::Definition::BeamMonitor>(fCheckOverlap);
    auto& target = acceleratorField.NewDaughter<Detector::Definition::Target>(fCheckOverlap);

    // 4

    auto& cdcSuperLayer = cdcGas.NewDaughter<Detector::Definition::CDCSuperLayer>(fCheckOverlap);

    // 5

    auto& cdcSenseLayer = cdcSuperLayer.NewDaughter<Detector::Definition::CDCSenseLayer>(fCheckOverlap);

    // 6

    auto& cdcCell = cdcSenseLayer.NewDaughter<Detector::Definition::CDCCell>(fCheckOverlap);

    ////////////////////////////////////////////////////////////////
    // Register materials
    ////////////////////////////////////////////////////////////////
    {
        using namespace MACE::LiteralUnit::Density;

        const auto nist = G4NistManager::Instance();

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
        // const auto defaultCuts = G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts();

        // CDCFieldWireRegion
        fCDCFieldWireRegion = new Region("CDCFieldWire", RegionType::CDCFieldWire);
        // fCDCFieldWireRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion("CDCFieldWire", fCDCFieldWireRegion);

        // CDCSenseWireRegion
        fCDCSenseWireRegion = new Region("CDCSenseWire", RegionType::CDCSenseWire);
        // fCDCSenseWireRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion("CDCSenseWire", fCDCSenseWireRegion);

        // DefaultGaseousRegion
        fDefaultGaseousRegion = new Region("DefaultGaseous", RegionType::DefaultGaseous);
        // fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion("CDCCell", fDefaultGaseousRegion);
        cdcGas.RegisterRegion(fDefaultGaseousRegion);
        cdcSenseLayer.RegisterRegion(fDefaultGaseousRegion);
        cdcSuperLayer.RegisterRegion(fDefaultGaseousRegion);

        // DefaultSolidRegion
        fDefaultSolidRegion = new Region("DefaultSolid", RegionType::DefaultSolid);
        // fDefaultSolidRegion->SetProductionCuts(defaultCuts);

        beamDegrader.RegisterRegion(fDefaultSolidRegion);
        beamMonitor.RegisterRegion(fDefaultSolidRegion);
        cdcBody.RegisterRegion(fDefaultSolidRegion);
        emcPMTAssemblies.RegisterRegion(fDefaultSolidRegion);
        filter.RegisterRegion(fDefaultSolidRegion);
        shieldingWall.RegisterRegion(fDefaultSolidRegion);

        // EMCSensitiveRegion
        fEMCSensitiveRegion = new Region("EMCSensitive", RegionType::EMCSensitive);
        // fEMCSensitiveRegion->SetProductionCuts(defaultCuts);

        emcCrystal.RegisterRegion(fEMCSensitiveRegion);

        // MCPSensitiveRegion
        fMCPSensitiveRegion = new Region("MCPSensitive", RegionType::MCPSensitive);
        // fMCPSensitiveRegion->SetProductionCuts(defaultCuts);

        mcp.RegisterRegion(fMCPSensitiveRegion);

        // ShieldRegion
        fShieldRegion = new Region("Shield", RegionType::Shield);
        // fShieldRegion->SetProductionCuts(defaultCuts);

        emcShield.RegisterRegion(fShieldRegion);
        spectrometerShield.RegisterRegion(fShieldRegion);

        // SolenoidOrMagnetRegion
        fSolenoidOrMagnetRegion = new Region("SolenoidOrMagnet", RegionType::SolenoidOrMagnet);
        // fSolenoidOrMagnetRegion->SetProductionCuts(defaultCuts);

        solenoidB1.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS1.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidB2.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS2.RegisterRegion(fSolenoidOrMagnetRegion);
        spectrometerMagnet.RegisterRegion(fSolenoidOrMagnetRegion);
        emcMagnet.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS3.RegisterRegion(fSolenoidOrMagnetRegion);

        // CDCSensitiveRegion
        fCDCSensitiveRegion = new Region("CDCSensitive", RegionType::CDCSensitive);
        // fCDCSensitiveRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion("CDCSensitiveVolume", fCDCSensitiveRegion);

        // TargetRegion
        fTargetRegion = new Region("Target", RegionType::Target);
        // fTargetRegion->SetProductionCuts(defaultCuts);

        target.RegisterRegion(fTargetRegion);

        // VacuumRegion
        fVacuumRegion = new Region("Vacuum", RegionType::Vacuum);
        // fVacuumRegion->SetProductionCuts(defaultCuts);

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
        fCDCSD = new SD::CDCSD{Detector::Description::CDC::Instance().Name()};
        cdcCell.RegisterSD("CDCSensitiveVolume", fCDCSD);

        fEMCSD = new SD::EMCSD{Detector::Description::EMC::Instance().Name()};
        emcCrystal.RegisterSD(fEMCSD);

        fMCPSD = new SD::MCPSD{Detector::Description::MCP::Instance().Name()};
        mcp.RegisterSD(fMCPSD);
    }

    ////////////////////////////////////////////////////////////////
    // Register background fields
    ////////////////////////////////////////////////////////////////
    {
        using namespace LiteralUnit::Length;
        using namespace LiteralUnit::MagneticFluxDensity;

        constexpr auto hMin = 100_um;

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
