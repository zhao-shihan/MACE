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
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

#include "gsl/gsl"

namespace MACE::SimMACE::inline Action {

using namespace Mustard::LiteralUnit::Length;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{},
    fMinDriverStep{2_um},
    fDeltaChord{2_um},
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
    fEMCSD{},
    fNumericMessengerRegister{this} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    // 0

    fWorld = std::make_unique<Detector::Definition::World>();

    // 1

    Detector::Assembly::MMS mms{*fWorld, fCheckOverlap};

    auto& emcField{fWorld->NewDaughter<Detector::Definition::EMCField>(fCheckOverlap)};
    auto& emcShield{fWorld->NewDaughter<Detector::Definition::EMCShield>(fCheckOverlap)};
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
    auto& mcpChamber{emcField.NewDaughter<Detector::Definition::MCPChamber>(fCheckOverlap)};

    auto& solenoidBeamPipeS1{solenoidFieldS1.NewDaughter<Detector::Definition::SolenoidBeamPipeS1>(fCheckOverlap)};
    auto& solenoidS1{solenoidFieldS1.NewDaughter<Detector::Definition::SolenoidS1>(fCheckOverlap)};
    auto& solenoidShieldS1{solenoidFieldS1.NewDaughter<Detector::Definition::SolenoidShieldS1>(fCheckOverlap)};

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

    // 3

    auto& mcp{mcpChamber.NewDaughter<Detector::Definition::MCP>(fCheckOverlap)};

    auto& acceleratorField{mms.Get<Detector::Definition::MMSBeamPipe>().NewDaughter<Detector::Definition::AcceleratorField>(fCheckOverlap)};

    auto& filter{solenoidBeamPipeS2.NewDaughter<Detector::Definition::Filter>(fCheckOverlap)};

    // 4

    auto& accelerator{acceleratorField.NewDaughter<Detector::Definition::Accelerator>(fCheckOverlap)};
    auto& beamDegrader{acceleratorField.NewDaughter<Detector::Definition::BeamDegrader>(fCheckOverlap)};
    auto& beamMonitor{acceleratorField.NewDaughter<Detector::Definition::BeamMonitor>(fCheckOverlap)};
    auto& target{acceleratorField.NewDaughter<Detector::Definition::Target>(fCheckOverlap)};

    ////////////////////////////////////////////////////////////////
    // Register regions
    ////////////////////////////////////////////////////////////////
    {
        const auto defaultCuts{G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts()};

        // CDCFieldWireRegion
        fCDCFieldWireRegion = new Region("CDCFieldWire", RegionType::CDCFieldWire);
        fCDCFieldWireRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::CDCCell>().RegisterRegion("CDCFieldWire", fCDCFieldWireRegion);

        // CDCSenseWireRegion
        fCDCSenseWireRegion = new Region("CDCSenseWire", RegionType::CDCSenseWire);
        fCDCSenseWireRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::CDCCell>().RegisterRegion("CDCSenseWire", fCDCSenseWireRegion);

        // DefaultGaseousRegion
        fDefaultGaseousRegion = new Region("DefaultGaseous", RegionType::DefaultGaseous);
        fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::CDCCell>().RegisterRegion("CDCCell", fDefaultGaseousRegion);
        mms.Get<Detector::Definition::CDCGas>().RegisterRegion(fDefaultGaseousRegion);
        mms.Get<Detector::Definition::CDCSenseLayer>().RegisterRegion(fDefaultGaseousRegion);
        mms.Get<Detector::Definition::CDCSuperLayer>().RegisterRegion(fDefaultGaseousRegion);
        emcField.RegisterRegion(fDefaultGaseousRegion);
        mms.Get<Detector::Definition::MMSField>().RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldS1.RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldS2.RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldS3.RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldT1.RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldT2.RegisterRegion(fDefaultGaseousRegion);

        // DefaultSolidRegion
        fDefaultSolidRegion = new Region("DefaultSolid", RegionType::DefaultSolid);
        fDefaultSolidRegion->SetProductionCuts(defaultCuts);

        accelerator.RegisterRegion(fDefaultSolidRegion);
        beamDegrader.RegisterRegion(fDefaultSolidRegion);
        beamMonitor.RegisterRegion(fDefaultSolidRegion);
        mms.Get<Detector::Definition::CDCBody>().RegisterRegion(fDefaultSolidRegion);
        emcPMTAssemblies.RegisterRegion(fDefaultSolidRegion);
        filter.RegisterRegion(fDefaultSolidRegion);
        mcpChamber.RegisterRegion(fDefaultSolidRegion);
        mms.Get<Detector::Definition::MMSBeamPipe>().RegisterRegion(fDefaultSolidRegion);
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
        mms.Get<Detector::Definition::MMSShield>().RegisterRegion(fShieldRegion);
        solenoidShieldS1.RegisterRegion(fShieldRegion);
        solenoidShieldS2.RegisterRegion(fShieldRegion);
        solenoidShieldS3.RegisterRegion(fShieldRegion);
        solenoidShieldT1.RegisterRegion(fShieldRegion);
        solenoidShieldT2.RegisterRegion(fShieldRegion);

        // SolenoidOrMagnetRegion
        fSolenoidOrMagnetRegion = new Region("SolenoidOrMagnet", RegionType::SolenoidOrMagnet);
        fSolenoidOrMagnetRegion->SetProductionCuts(defaultCuts);

        emcMagnet.RegisterRegion(fSolenoidOrMagnetRegion);
        mms.Get<Detector::Definition::MMSMagnet>().RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS1.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS2.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidS3.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidT1.RegisterRegion(fSolenoidOrMagnetRegion);
        solenoidT2.RegisterRegion(fSolenoidOrMagnetRegion);

        // CDCSensitiveRegion
        fCDCSensitiveRegion = new Region("CDCSensitive", RegionType::CDCSensitive);
        fCDCSensitiveRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::CDCCell>().RegisterRegion("CDCSensitiveVolume", fCDCSensitiveRegion);

        // TTCSensitiveRegionRegion
        fTTCSensitiveRegion = new Region("TTCSensitiveRegion", RegionType::TTCSensitive);
        fTTCSensitiveRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::TTC>().RegisterRegion(fTTCSensitiveRegion);

        // TargetRegion
        fTargetRegion = new Region("Target", RegionType::Target);
        fTargetRegion->SetProductionCuts(defaultCuts);

        target.RegisterRegion(fTargetRegion);

        // VacuumRegion
        fVacuumRegion = new Region("Vacuum", RegionType::Vacuum);
        fVacuumRegion->SetProductionCuts(defaultCuts);

        acceleratorField.RegisterRegion(fVacuumRegion);
        mcpChamber.RegisterRegion("MCPChamberPipeVacuum", fVacuumRegion);
        mcpChamber.RegisterRegion("MCPChamberVacuum", fVacuumRegion);
        mms.Get<Detector::Definition::MMSBeamPipe>().RegisterRegion("MMSBeamPipeVacuum", fVacuumRegion);
        solenoidBeamPipeS1.RegisterRegion("SolenoidBeamPipeS1Vacuum", fVacuumRegion);
        solenoidBeamPipeS2.RegisterRegion("SolenoidBeamPipeS2Vacuum", fVacuumRegion);
        solenoidBeamPipeS3.RegisterRegion("SolenoidBeamPipeS3Vacuum", fVacuumRegion);
        solenoidBeamPipeT1.RegisterRegion("SolenoidBeamPipeT1Vacuum", fVacuumRegion);
        solenoidBeamPipeT2.RegisterRegion("SolenoidBeamPipeT2Vacuum", fVacuumRegion);
    }

    ////////////////////////////////////////////////////////////////
    // Register SDs
    ////////////////////////////////////////////////////////////////
    {
        fCDCSD = new SD::CDCSD{Detector::Description::CDC::Instance().Name()};
        mms.Get<Detector::Definition::CDCCell>().RegisterSD("CDCSensitiveVolume", fCDCSD);

        fTTCSD = new SD::TTCSD{Detector::Description::TTC::Instance().Name()};
        mms.Get<Detector::Definition::TTC>().RegisterSD(fTTCSD);

        fMCPSD = new SD::MCPSD{Detector::Description::MCP::Instance().Name()};
        mcp.RegisterSD(fMCPSD);

        fEMCSD = new SD::EMCSD{Detector::Description::EMC::Instance().Name()};
        emcCrystal.RegisterSD(fEMCSD);
    }

    ////////////////////////////////////////////////////////////////
    // Register background fields
    ////////////////////////////////////////////////////////////////
    {
        { // Magnetic fields
            const auto RegisterField{
                [this]<typename AField>(Mustard::Detector::Definition::DefinitionBase& detector, AField* field, bool forceToAllDaughters) {
                    using Equation = G4TMagFieldEquation<AField>;
                    using Stepper = G4TDormandPrince45<Equation, 6>;
                    using Driver = G4InterpolationDriver<Stepper>;
                    const auto equation{new Equation{field}}; // clang-format off
                    const auto stepper{new Stepper{equation, 6}};
                    const auto driver{new Driver{fMinDriverStep, stepper, 6}}; // clang-format on
                    const auto chordFinder{new G4ChordFinder{driver}};
                    chordFinder->SetDeltaChord(fDeltaChord);
                    detector.RegisterField(std::make_unique<G4FieldManager>(field, chordFinder), forceToAllDaughters);
                }};
            RegisterField(mms.Get<Detector::Definition::MMSField>(), new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::MMSField>, false);
            RegisterField(solenoidFieldS1, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldS1>, false);
            RegisterField(solenoidFieldT1, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldT1>, false);
            RegisterField(solenoidFieldS2, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldS2>, false);
            RegisterField(solenoidFieldT2, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldT2>, false);
            RegisterField(solenoidFieldS3, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldS3>, false);
            RegisterField(emcField, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::EMCField>, false);
        }
        { // Accelerator EM field, must be reigstered after MMS magnetic field
            using Field = Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::AcceleratorField>;
            using Equation = G4EqMagElectricField;
            using Stepper = G4TDormandPrince45<Equation, 8>;
            using Driver = G4InterpolationDriver<Stepper>;
            const auto field{new Field};
            const auto equation{new Equation{field}}; // clang-format off
            const auto stepper{new Stepper{equation, 8}};
            const auto driver{new Driver{fMinDriverStep, stepper, 8}}; // clang-format on
            const auto chordFinder{new G4ChordFinder{driver}};
            chordFinder->SetDeltaChord(fDeltaChord);
            acceleratorField.RegisterField(std::make_unique<G4FieldManager>(field, chordFinder), false);
        }
    }

    return fWorld->PhysicalVolume();
}

} // namespace MACE::SimMACE::inline Action
