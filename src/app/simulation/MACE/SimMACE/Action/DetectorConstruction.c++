#include "MACE/Detector/Definition/Accelerator.h++"
#include "MACE/Detector/Definition/AcceleratorField.h++"
#include "MACE/Detector/Definition/BeamDegrader.h++"
#include "MACE/Detector/Definition/BeamMonitor.h++"
#include "MACE/Detector/Definition/CDCBody.h++"
#include "MACE/Detector/Definition/CDCCell.h++"
#include "MACE/Detector/Definition/CDCGas.h++"
#include "MACE/Detector/Definition/CDCSenseLayer.h++"
#include "MACE/Detector/Definition/CDCSuperLayer.h++"
#include "MACE/Detector/Definition/EMCCrystal.h++"
#include "MACE/Detector/Definition/EMCField.h++"
#include "MACE/Detector/Definition/EMCMagnet.h++"
#include "MACE/Detector/Definition/EMCPMTAssemblies.h++"
#include "MACE/Detector/Definition/EMCShield.h++"
#include "MACE/Detector/Definition/Filter.h++"
#include "MACE/Detector/Definition/MCP.h++"
#include "MACE/Detector/Definition/MCPChamber.h++"
#include "MACE/Detector/Definition/MMSBeamPipe.h++"
#include "MACE/Detector/Definition/MMSField.h++"
#include "MACE/Detector/Definition/MMSMagnet.h++"
#include "MACE/Detector/Definition/MMSShield.h++"
#include "MACE/Detector/Definition/ShieldingWall.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeS1.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeS2.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeS3.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeT1.h++"
#include "MACE/Detector/Definition/SolenoidBeamPipeT2.h++"
#include "MACE/Detector/Definition/SolenoidFieldS1.h++"
#include "MACE/Detector/Definition/SolenoidFieldS2.h++"
#include "MACE/Detector/Definition/SolenoidFieldS3.h++"
#include "MACE/Detector/Definition/SolenoidFieldT1.h++"
#include "MACE/Detector/Definition/SolenoidFieldT2.h++"
#include "MACE/Detector/Definition/SolenoidS1.h++"
#include "MACE/Detector/Definition/SolenoidS2.h++"
#include "MACE/Detector/Definition/SolenoidS3.h++"
#include "MACE/Detector/Definition/SolenoidShieldS1.h++"
#include "MACE/Detector/Definition/SolenoidShieldS2.h++"
#include "MACE/Detector/Definition/SolenoidShieldS3.h++"
#include "MACE/Detector/Definition/SolenoidShieldT1.h++"
#include "MACE/Detector/Definition/SolenoidShieldT2.h++"
#include "MACE/Detector/Definition/SolenoidT1.h++"
#include "MACE/Detector/Definition/SolenoidT2.h++"
#include "MACE/Detector/Definition/TTC.h++"
#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Field/AcceleratorField.h++"
#include "MACE/Detector/Field/EMCField.h++"
#include "MACE/Detector/Field/MMSField.h++"
#include "MACE/Detector/Field/SolenoidFieldS1.h++"
#include "MACE/Detector/Field/SolenoidFieldS2.h++"
#include "MACE/Detector/Field/SolenoidFieldS3.h++"
#include "MACE/Detector/Field/SolenoidFieldT1.h++"
#include "MACE/Detector/Field/SolenoidFieldT2.h++"
#include "MACE/SimMACE/Action/DetectorConstruction.h++"
#include "MACE/SimMACE/Messenger/DetectorMessenger.h++"
#include "MACE/SimMACE/SD/CDCSD.h++"
#include "MACE/SimMACE/SD/EMCSD.h++"
#include "MACE/SimMACE/SD/MCPSD.h++"
#include "MACE/SimMACE/SD/TTCSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Field/AsG4Field.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4ChordFinder.hh"
#include "G4EqMagElectricField.hh"
#include "G4InterpolationDriver.hh"
#include "G4NistManager.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

#include "gsl/gsl"

namespace MACE::SimMACE::inline Action {

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{},
    fWorld{},
    fCDCFieldWireRegion{},
    fCDCSenseWireRegion{},
    fCDCSensitiveRegion{},
    fDefaultGaseousRegion{},
    fDefaultSolidRegion{},
    fEMCSensitiveRegion{},
    fMCPSensitiveRegion{},
    fShieldRegion{},
    fSolenoidOrMagnetRegion{},
    fTTCSensitiveRegion{},
    fTargetRegion{},
    fVacuumRegion{},
    fCDCSD{},
    fTTCSD{},
    fMCPSD{},
    fEMCSD{} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    // 0

    fWorld = std::make_unique<Detector::Definition::World>();

    // 1

    auto& emcField{fWorld->NewDaughter<Detector::Definition::EMCField>(fCheckOverlap)};
    auto& emcShield{fWorld->NewDaughter<Detector::Definition::EMCShield>(fCheckOverlap)};
    auto& mmsField{fWorld->NewDaughter<Detector::Definition::MMSField>(fCheckOverlap)};
    auto& mmsShield{fWorld->NewDaughter<Detector::Definition::MMSShield>(fCheckOverlap)};
    auto& shieldingWall{fWorld->NewDaughter<Detector::Definition::ShieldingWall>(fCheckOverlap)};
    auto& solenoidFieldS1{fWorld->NewDaughter<Detector::Definition::SolenoidFieldS1>(fCheckOverlap)};
    auto& solenoidFieldS2{fWorld->NewDaughter<Detector::Definition::SolenoidFieldS2>(fCheckOverlap)};
    auto& solenoidFieldS3{fWorld->NewDaughter<Detector::Definition::SolenoidFieldS3>(fCheckOverlap)};
    auto& solenoidFieldT1{fWorld->NewDaughter<Detector::Definition::SolenoidFieldT1>(fCheckOverlap)};
    auto& solenoidFieldT2{fWorld->NewDaughter<Detector::Definition::SolenoidFieldT2>(fCheckOverlap)};

    // 2

    auto& emcCrystal{emcField.NewDaughter<Detector::Definition::EMCCrystal>(fCheckOverlap)};
    auto& emcMagnet{emcField.NewDaughter<Detector::Definition::EMCMagnet>(fCheckOverlap)};
    auto& emcPMTAssemblies{emcField.NewDaughter<Detector::Definition::EMCPMTAssemblies>(fCheckOverlap)};
    auto& mcp{emcField.NewDaughter<Detector::Definition::MCP>(fCheckOverlap)};
    auto& mcpChamber{emcField.NewDaughter<Detector::Definition::MCPChamber>(fCheckOverlap)};

    auto& solenoidBeamPipeS1{solenoidFieldS1.NewDaughter<Detector::Definition::SolenoidBeamPipeS1>(fCheckOverlap)};
    auto& solenoidS1{solenoidFieldS1.NewDaughter<Detector::Definition::SolenoidS1>(fCheckOverlap)};
    auto& solenoidShieldS1{solenoidFieldS1.NewDaughter<Detector::Definition::SolenoidShieldS1>(fCheckOverlap)};

    auto& filter{solenoidFieldS2.NewDaughter<Detector::Definition::Filter>(fCheckOverlap)};
    auto& solenoidBeamPipeS2{solenoidFieldS2.NewDaughter<Detector::Definition::SolenoidBeamPipeS2>(fCheckOverlap)};
    auto& solenoidS2{solenoidFieldS2.NewDaughter<Detector::Definition::SolenoidS2>(fCheckOverlap)};
    auto& solenoidShieldS2{solenoidFieldS2.NewDaughter<Detector::Definition::SolenoidShieldS2>(fCheckOverlap)};

    auto& solenoidBeamPipeS3{solenoidFieldS3.NewDaughter<Detector::Definition::SolenoidBeamPipeS3>(fCheckOverlap)};
    auto& solenoidS3{solenoidFieldS3.NewDaughter<Detector::Definition::SolenoidS3>(fCheckOverlap)};
    auto& solenoidShieldS3{solenoidFieldS3.NewDaughter<Detector::Definition::SolenoidShieldS3>(fCheckOverlap)};

    auto& solenoidBeamPipeT1{solenoidFieldT1.NewDaughter<Detector::Definition::SolenoidBeamPipeT1>(fCheckOverlap)};
    auto& solenoidShieldT1{solenoidFieldT1.NewDaughter<Detector::Definition::SolenoidShieldT1>(fCheckOverlap)};
    auto& solenoidT1{solenoidFieldT1.NewDaughter<Detector::Definition::SolenoidT1>(fCheckOverlap)};

    auto& solenoidBeamPipeT2{solenoidFieldT2.NewDaughter<Detector::Definition::SolenoidBeamPipeT2>(fCheckOverlap)};
    auto& solenoidShieldT2{solenoidFieldT2.NewDaughter<Detector::Definition::SolenoidShieldT2>(fCheckOverlap)};
    auto& solenoidT2{solenoidFieldT2.NewDaughter<Detector::Definition::SolenoidT2>(fCheckOverlap)};

    auto& acceleratorField{mmsField.NewDaughter<Detector::Definition::AcceleratorField>(fCheckOverlap)};
    auto& cdcBody{mmsField.NewDaughter<Detector::Definition::CDCBody>(fCheckOverlap)};
    auto& mmsBeamPipe{mmsField.NewDaughter<Detector::Definition::MMSBeamPipe>(fCheckOverlap)};
    auto& mmsMagnet{mmsField.NewDaughter<Detector::Definition::MMSMagnet>(fCheckOverlap)};
    auto& ttc{mmsField.NewDaughter<Detector::Definition::TTC>(fCheckOverlap)};

    // 3

    auto& cdcGas{cdcBody.NewDaughter<Detector::Definition::CDCGas>(fCheckOverlap)};

    auto& accelerator{acceleratorField.NewDaughter<Detector::Definition::Accelerator>(fCheckOverlap)};
    auto& beamDegrader{acceleratorField.NewDaughter<Detector::Definition::BeamDegrader>(fCheckOverlap)};
    auto& beamMonitor{acceleratorField.NewDaughter<Detector::Definition::BeamMonitor>(fCheckOverlap)};
    auto& target{acceleratorField.NewDaughter<Detector::Definition::Target>(fCheckOverlap)};

    // 4

    auto& cdcSuperLayer{cdcGas.NewDaughter<Detector::Definition::CDCSuperLayer>(fCheckOverlap)};

    // 5

    auto& cdcSenseLayer{cdcSuperLayer.NewDaughter<Detector::Definition::CDCSenseLayer>(fCheckOverlap)};

    // 6

    auto& cdcCell{cdcSenseLayer.NewDaughter<Detector::Definition::CDCCell>(fCheckOverlap)};

    ////////////////////////////////////////////////////////////////
    // Register materials
    ////////////////////////////////////////////////////////////////
    {
        using namespace Mustard::LiteralUnit::Density;

        const auto nist = G4NistManager::Instance();

        const auto vacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3);
        acceleratorField.RegisterMaterial(vacuum);
        emcField.RegisterMaterial(vacuum);
        fWorld->RegisterMaterial(vacuum);
        mmsField.RegisterMaterial(vacuum);
        solenoidFieldS1.RegisterMaterial(vacuum);
        solenoidFieldS2.RegisterMaterial(vacuum);
        solenoidFieldS3.RegisterMaterial(vacuum);
        solenoidFieldT1.RegisterMaterial(vacuum);
        solenoidFieldT2.RegisterMaterial(vacuum);
    }

    ////////////////////////////////////////////////////////////////
    // Register regions
    ////////////////////////////////////////////////////////////////
    {
        const auto defaultCuts{G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts()};

        // CDCFieldWireRegion
        fCDCFieldWireRegion = new Region("CDCFieldWire", RegionType::CDCFieldWire);
        fCDCFieldWireRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion("CDCFieldWire", fCDCFieldWireRegion);

        // CDCSenseWireRegion
        fCDCSenseWireRegion = new Region("CDCSenseWire", RegionType::CDCSenseWire);
        fCDCSenseWireRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion("CDCSenseWire", fCDCSenseWireRegion);

        // DefaultGaseousRegion
        fDefaultGaseousRegion = new Region("DefaultGaseous", RegionType::DefaultGaseous);
        fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion("CDCCell", fDefaultGaseousRegion);
        cdcGas.RegisterRegion(fDefaultGaseousRegion);
        cdcSenseLayer.RegisterRegion(fDefaultGaseousRegion);
        cdcSuperLayer.RegisterRegion(fDefaultGaseousRegion);

        // DefaultSolidRegion
        fDefaultSolidRegion = new Region("DefaultSolid", RegionType::DefaultSolid);
        fDefaultSolidRegion->SetProductionCuts(defaultCuts);

        accelerator.RegisterRegion(fDefaultSolidRegion);
        beamDegrader.RegisterRegion(fDefaultSolidRegion);
        beamMonitor.RegisterRegion(fDefaultSolidRegion);
        cdcBody.RegisterRegion(fDefaultSolidRegion);
        emcPMTAssemblies.RegisterRegion(fDefaultSolidRegion);
        filter.RegisterRegion(fDefaultSolidRegion);
        mcpChamber.RegisterRegion(fDefaultSolidRegion);
        mmsBeamPipe.RegisterRegion(fDefaultSolidRegion);
        shieldingWall.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeS1.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeS2.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeS3.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeT1.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeT2.RegisterRegion(fDefaultSolidRegion);

        // EMCSensitiveRegion
        fEMCSensitiveRegion = new Region("EMCSensitive", RegionType::EMCSensitive);
        fEMCSensitiveRegion->SetProductionCuts(defaultCuts);

        emcCrystal.RegisterRegion(fEMCSensitiveRegion);

        // MCPSensitiveRegion
        fMCPSensitiveRegion = new Region("MCPSensitive", RegionType::MCPSensitive);
        fMCPSensitiveRegion->SetProductionCuts(defaultCuts);

        mcp.RegisterRegion(fMCPSensitiveRegion);

        // ShieldRegion
        fShieldRegion = new Region("Shield", RegionType::Shield);
        fShieldRegion->SetProductionCuts(defaultCuts);

        emcShield.RegisterRegion(fShieldRegion);
        mmsShield.RegisterRegion(fShieldRegion);
        solenoidShieldS1.RegisterRegion(fShieldRegion);
        solenoidShieldS2.RegisterRegion(fShieldRegion);
        solenoidShieldS3.RegisterRegion(fShieldRegion);
        solenoidShieldT1.RegisterRegion(fShieldRegion);
        solenoidShieldT2.RegisterRegion(fShieldRegion);

        // SolenoidOrMagnetRegion
        fSolenoidOrMagnetRegion = new Region("SolenoidOrMagnet", RegionType::SolenoidOrMagnet);
        fSolenoidOrMagnetRegion->SetProductionCuts(defaultCuts);

        emcMagnet.RegisterRegion(fSolenoidOrMagnetRegion);
        mmsMagnet.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS1.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS2.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS3.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidT1.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidT2.RegisterRegion(fSolenoidOrMagnetRegion);

        // CDCSensitiveRegion
        fCDCSensitiveRegion = new Region("CDCSensitive", RegionType::CDCSensitive);
        fCDCSensitiveRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion("CDCSensitiveVolume", fCDCSensitiveRegion);

        // TTCSensitiveRegionRegion
        fTTCSensitiveRegion = new Region("TTCSensitiveRegion", RegionType::TTCSensitive);
        fTTCSensitiveRegion->SetProductionCuts(defaultCuts);

        ttc.RegisterRegion(fTTCSensitiveRegion);

        // TargetRegion
        fTargetRegion = new Region("Target", RegionType::Target);
        fTargetRegion->SetProductionCuts(defaultCuts);

        target.RegisterRegion(fTargetRegion);

        // VacuumRegion
        fVacuumRegion = new Region("Vacuum", RegionType::Vacuum);
        fVacuumRegion->SetProductionCuts(defaultCuts);

        acceleratorField.RegisterRegion(fVacuumRegion);
        emcField.RegisterRegion(fVacuumRegion);
        mmsField.RegisterRegion(fVacuumRegion);
        solenoidFieldS1.RegisterRegion(fVacuumRegion);
        solenoidFieldS2.RegisterRegion(fVacuumRegion);
        solenoidFieldS3.RegisterRegion(fVacuumRegion);
        solenoidFieldT1.RegisterRegion(fVacuumRegion);
        solenoidFieldT2.RegisterRegion(fVacuumRegion);
    }

    ////////////////////////////////////////////////////////////////
    // Register SDs
    ////////////////////////////////////////////////////////////////
    {
        fCDCSD = new SD::CDCSD{Detector::Description::CDC::Instance().Name()};
        cdcCell.RegisterSD("CDCSensitiveVolume", fCDCSD);

        fTTCSD = new SD::TTCSD{Detector::Description::TTC::Instance().Name()};
        ttc.RegisterSD(fTTCSD);

        fMCPSD = new SD::MCPSD{Detector::Description::MCP::Instance().Name()};
        mcp.RegisterSD(fMCPSD);

        fEMCSD = new SD::EMCSD{Detector::Description::EMC::Instance().Name()};
        emcCrystal.RegisterSD(fEMCSD);
    }

    ////////////////////////////////////////////////////////////////
    // Register background fields
    ////////////////////////////////////////////////////////////////
    {
        using namespace Mustard::LiteralUnit::Length;
        using namespace Mustard::LiteralUnit::MagneticFluxDensity;

        constexpr auto hMin{1_um};
        { // magnetic field
            const auto RegisterMagneticField{
                []<typename AField>(Mustard::Detector::Definition::DefinitionBase& detector, AField* field, bool forceToAllDaughters) {
                    using Equation = G4TMagFieldEquation<AField>;
                    using Stepper = G4TDormandPrince45<Equation, 6>;
                    using Driver = G4InterpolationDriver<Stepper>;
                    const auto equation{new Equation{field}}; // clang-format off
                    const auto stepper{new Stepper{equation, 6}};
                    const auto driver{new Driver{hMin, stepper, 6}}; // clang-format on
                    const auto chordFinder{new G4ChordFinder{driver}};
                    detector.RegisterField(std::make_unique<G4FieldManager>(field, chordFinder), forceToAllDaughters);
                }};
            RegisterMagneticField(mmsField, new Mustard::Detector::Field::AsG4Field<Detector::Field::MMSField>, false);
            RegisterMagneticField(solenoidFieldS1, new Mustard::Detector::Field::AsG4Field<Detector::Field::SolenoidFieldS1>, false);
            RegisterMagneticField(solenoidFieldT1, new Mustard::Detector::Field::AsG4Field<Detector::Field::SolenoidFieldT1>, false);
            RegisterMagneticField(solenoidFieldS2, new Mustard::Detector::Field::AsG4Field<Detector::Field::SolenoidFieldS2>, false);
            RegisterMagneticField(solenoidFieldT2, new Mustard::Detector::Field::AsG4Field<Detector::Field::SolenoidFieldT2>, false);
            RegisterMagneticField(solenoidFieldS3, new Mustard::Detector::Field::AsG4Field<Detector::Field::SolenoidFieldS3>, false);
            RegisterMagneticField(emcField, new Mustard::Detector::Field::AsG4Field<Detector::Field::EMCField>, false);
        }
        { // EM field, must be reigstered after MMS magnetic field! but why?
            using Equation = G4EqMagElectricField;
            using Stepper = G4TDormandPrince45<Equation, 8>;
            using Driver = G4InterpolationDriver<Stepper>;
            const auto field{new Mustard::Detector::Field::AsG4Field<Detector::Field::AcceleratorField>};
            const auto equation{new Equation{field}}; // clang-format off
            const auto stepper{new Stepper{equation, 8}};
            const auto driver{new Driver{hMin, stepper, 8}}; // clang-format on
            const auto chordFinder{new G4ChordFinder{driver}};
            acceleratorField.RegisterField(std::make_unique<G4FieldManager>(field, chordFinder), false);
        }
    }

    return fWorld->PhysicalVolume();
}

} // namespace MACE::SimMACE::inline Action
