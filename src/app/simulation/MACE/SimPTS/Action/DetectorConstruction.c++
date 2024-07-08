#include "MACE/Detector/Definition/Accelerator.h++"
#include "MACE/Detector/Definition/AcceleratorField.h++"
#include "MACE/Detector/Definition/EMCField.h++"
#include "MACE/Detector/Definition/EMCMagnet.h++"
#include "MACE/Detector/Definition/EMCShield.h++"
#include "MACE/Detector/Definition/Filter.h++"
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
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Field/AcceleratorField.h++"
#include "MACE/Detector/Field/EMCField.h++"
#include "MACE/Detector/Field/MMSField.h++"
#include "MACE/Detector/Field/SolenoidFieldS1.h++"
#include "MACE/Detector/Field/SolenoidFieldS2.h++"
#include "MACE/Detector/Field/SolenoidFieldS3.h++"
#include "MACE/Detector/Field/SolenoidFieldT1.h++"
#include "MACE/Detector/Field/SolenoidFieldT2.h++"
#include "MACE/SimPTS/Action/DetectorConstruction.h++"
#include "MACE/SimPTS/Detector/Definition/VirtualDetectorA.h++"
#include "MACE/SimPTS/Detector/Definition/VirtualDetectorB.h++"
#include "MACE/SimPTS/Detector/Definition/VirtualDetectorC.h++"
#include "MACE/SimPTS/Detector/Definition/VirtualDetectorD.h++"
#include "MACE/SimPTS/Messenger/DetectorMessenger.h++"
#include "MACE/SimPTS/SD/VirtualSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Field/AsG4Field.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4BFieldIntegrationDriver.hh"
#include "G4ChordFinder.hh"
#include "G4EqMagElectricField.hh"
#include "G4HelixHeum.hh"
#include "G4IntegrationDriver.hh"
#include "G4InterpolationDriver.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

#include "gsl/gsl"

namespace MACE::SimPTS::inline Action {

using namespace Mustard::LiteralUnit::Length;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{},
    fMinDriverStep{0.1_um},
    fDeltaChord{1_um},
    fWorld{},
    fDefaultGaseousRegion{},
    fDefaultSolidRegion{},
    fShieldRegion{},
    fSolenoidOrMagnetRegion{},
    fVacuumRegion{},
    fNumericMessengerRegister{this} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    // 0

    fWorld = std::make_unique<MACE::Detector::Definition::World>();

    // 1

    auto& emcField{fWorld->NewDaughter<MACE::Detector::Definition::EMCField>(fCheckOverlap)};
    auto& emcShield{fWorld->NewDaughter<MACE::Detector::Definition::EMCShield>(fCheckOverlap)};
    auto& mmsField{fWorld->NewDaughter<MACE::Detector::Definition::MMSField>(fCheckOverlap)};
    auto& mmsShield{fWorld->NewDaughter<MACE::Detector::Definition::MMSShield>(fCheckOverlap)};
    auto& shieldingWall{fWorld->NewDaughter<MACE::Detector::Definition::ShieldingWall>(fCheckOverlap)};
    auto& solenoidFieldS1{fWorld->NewDaughter<MACE::Detector::Definition::SolenoidFieldS1>(fCheckOverlap)};
    auto& solenoidFieldS2{fWorld->NewDaughter<MACE::Detector::Definition::SolenoidFieldS2>(fCheckOverlap)};
    auto& solenoidFieldS3{fWorld->NewDaughter<MACE::Detector::Definition::SolenoidFieldS3>(fCheckOverlap)};
    auto& solenoidFieldT1{fWorld->NewDaughter<MACE::Detector::Definition::SolenoidFieldT1>(fCheckOverlap)};
    auto& solenoidFieldT2{fWorld->NewDaughter<MACE::Detector::Definition::SolenoidFieldT2>(fCheckOverlap)};

    // 2

    auto& emcMagnet{emcField.NewDaughter<MACE::Detector::Definition::EMCMagnet>(fCheckOverlap)};
    auto& mcpChamber{emcField.NewDaughter<MACE::Detector::Definition::MCPChamber>(fCheckOverlap)};

    auto& solenoidBeamPipeS1{solenoidFieldS1.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeS1>(fCheckOverlap)};
    auto& solenoidS1{solenoidFieldS1.NewDaughter<MACE::Detector::Definition::SolenoidS1>(fCheckOverlap)};
    auto& solenoidShieldS1{solenoidFieldS1.NewDaughter<MACE::Detector::Definition::SolenoidShieldS1>(fCheckOverlap)};

    auto& solenoidBeamPipeS2{solenoidFieldS2.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeS2>(fCheckOverlap)};
    auto& solenoidS2{solenoidFieldS2.NewDaughter<MACE::Detector::Definition::SolenoidS2>(fCheckOverlap)};
    auto& solenoidShieldS2{solenoidFieldS2.NewDaughter<MACE::Detector::Definition::SolenoidShieldS2>(fCheckOverlap)};

    auto& solenoidBeamPipeS3{solenoidFieldS3.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeS3>(fCheckOverlap)};
    auto& solenoidS3{solenoidFieldS3.NewDaughter<MACE::Detector::Definition::SolenoidS3>(fCheckOverlap)};
    auto& solenoidShieldS3{solenoidFieldS3.NewDaughter<MACE::Detector::Definition::SolenoidShieldS3>(fCheckOverlap)};

    auto& solenoidBeamPipeT1{solenoidFieldT1.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeT1>(fCheckOverlap)};
    auto& solenoidShieldT1{solenoidFieldT1.NewDaughter<MACE::Detector::Definition::SolenoidShieldT1>(fCheckOverlap)};
    auto& solenoidT1{solenoidFieldT1.NewDaughter<MACE::Detector::Definition::SolenoidT1>(fCheckOverlap)};

    auto& solenoidBeamPipeT2{solenoidFieldT2.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeT2>(fCheckOverlap)};
    auto& solenoidShieldT2{solenoidFieldT2.NewDaughter<MACE::Detector::Definition::SolenoidShieldT2>(fCheckOverlap)};
    auto& solenoidT2{solenoidFieldT2.NewDaughter<MACE::Detector::Definition::SolenoidT2>(fCheckOverlap)};

    auto& mmsBeamPipe{mmsField.NewDaughter<MACE::Detector::Definition::MMSBeamPipe>(fCheckOverlap)};
    auto& mmsMagnet{mmsField.NewDaughter<MACE::Detector::Definition::MMSMagnet>(fCheckOverlap)};

    // 3

    auto& virtualDetectorD{mcpChamber.NewDaughter<Detector::Definition::VirtualDetectorD>(fCheckOverlap)};

    auto& filter{solenoidBeamPipeS2.NewDaughter<MACE::Detector::Definition::Filter>(fCheckOverlap)};
    auto& virtualDetectorB{solenoidBeamPipeS2.NewDaughter<Detector::Definition::VirtualDetectorB>(fCheckOverlap)};
    auto& virtualDetectorC{solenoidBeamPipeS2.NewDaughter<Detector::Definition::VirtualDetectorC>(fCheckOverlap)};

    auto& acceleratorField{mmsBeamPipe.NewDaughter<MACE::Detector::Definition::AcceleratorField>(fCheckOverlap)};
    auto& virtualDetectorA{mmsBeamPipe.NewDaughter<Detector::Definition::VirtualDetectorA>(fCheckOverlap)};

    // 4

    auto& accelerator{acceleratorField.NewDaughter<MACE::Detector::Definition::Accelerator>(fCheckOverlap)};

    ////////////////////////////////////////////////////////////////
    // Register regions
    ////////////////////////////////////////////////////////////////
    {
        const auto defaultCuts{G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts()};

        // DefaultGaseousRegion
        fDefaultGaseousRegion = new Region("DefaultGaseous", RegionType::DefaultGaseous);
        fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

        emcField.RegisterRegion(fDefaultGaseousRegion);
        mmsField.RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldS1.RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldS2.RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldS3.RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldT1.RegisterRegion(fDefaultGaseousRegion);
        solenoidFieldT2.RegisterRegion(fDefaultGaseousRegion);

        // DefaultSolidRegion
        fDefaultSolidRegion = new Region("DefaultSolid", RegionType::DefaultSolid);
        fDefaultSolidRegion->SetProductionCuts(defaultCuts);

        accelerator.RegisterRegion(fDefaultSolidRegion);
        filter.RegisterRegion(fDefaultSolidRegion);
        mcpChamber.RegisterRegion(fDefaultSolidRegion);
        mmsBeamPipe.RegisterRegion(fDefaultSolidRegion);
        shieldingWall.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeS1.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeS2.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeS3.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeT1.RegisterRegion(fDefaultSolidRegion);
        solenoidBeamPipeT2.RegisterRegion(fDefaultSolidRegion);

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

        // VacuumRegion
        fVacuumRegion = new Region("Vacuum", RegionType::Vacuum);
        fVacuumRegion->SetProductionCuts(defaultCuts);

        acceleratorField.RegisterRegion(fVacuumRegion);
        mcpChamber.RegisterRegion("MCPChamberPipeVacuum", fVacuumRegion);
        mcpChamber.RegisterRegion("MCPChamberVacuum", fVacuumRegion);
        mmsBeamPipe.RegisterRegion("MMSBeamPipeVacuum", fVacuumRegion);
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
        fVirtualSD = new SD::VirtualSD{"VirtualDetector"};
        virtualDetectorA.RegisterSD(fVirtualSD);
        virtualDetectorB.RegisterSD(fVirtualSD);
        virtualDetectorC.RegisterSD(fVirtualSD);
        virtualDetectorD.RegisterSD(fVirtualSD);
    }

    ////////////////////////////////////////////////////////////////
    // Register background fields
    ////////////////////////////////////////////////////////////////
    {
        const auto fieldOfMMSField{new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::MMSField>};
        const auto fieldOfSolenoidFieldS1{new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldS1>};
        const auto fieldOfSolenoidFieldT1{new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldT1>};
        const auto fieldOfSolenoidFieldS2{new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldS2>};
        const auto fieldOfSolenoidFieldT2{new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldT2>};
        const auto fieldOfSolenoidFieldS3{new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldS3>};
        const auto fieldOfEMCField{new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::EMCField>};

        { // Regular magnetic field
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
            RegisterField(mmsField, fieldOfMMSField, false);
            RegisterField(solenoidFieldS1, fieldOfSolenoidFieldS1, false);
            RegisterField(solenoidFieldT1, fieldOfSolenoidFieldT1, false);
            RegisterField(solenoidFieldS2, fieldOfSolenoidFieldS2, false);
            RegisterField(solenoidFieldT2, fieldOfSolenoidFieldT2, false);
            RegisterField(solenoidFieldS3, fieldOfSolenoidFieldS3, false);
            RegisterField(emcField, fieldOfEMCField, false);
        }
        { // Magnetic field in vacuum, use helix-based driver
            const auto RegisterField{
                [this]<typename AField>(Mustard::Detector::Definition::DefinitionBase& detector, std::string_view name,
                                        AField* field, bool forceToAllDaughters) {
                    using Equation = G4TMagFieldEquation<AField>;
                    using ShortStepper = G4TDormandPrince45<Equation, 6>;
                    using LongStepper = G4HelixHeum;
                    using ShortStepDriver = G4InterpolationDriver<ShortStepper>;
                    using LongStepDriver = G4IntegrationDriver<LongStepper>;
                    const auto equation{new Equation{field}};
                    const auto shortStepper{new ShortStepper{equation}};
                    const auto longStepper{new LongStepper{equation}};
                    auto shortdriver{std::make_unique<ShortStepDriver>(fMinDriverStep, shortStepper, 6)};
                    auto longDriver{std::make_unique<LongStepDriver>(fMinDriverStep, longStepper, 6)}; // clang-format off
                    const auto driver{new G4BFieldIntegrationDriver{std::move(shortdriver), std::move(longDriver)}}; // clang-format on
                    const auto chordFinder{new G4ChordFinder{driver}};
                    chordFinder->SetDeltaChord(fDeltaChord);
                    detector.RegisterField(name, std::make_unique<G4FieldManager>(field, chordFinder), forceToAllDaughters);
                }};
            RegisterField(mmsBeamPipe, "MMSBeamPipeVacuum", fieldOfMMSField, false);
            RegisterField(solenoidBeamPipeS1, "SolenoidBeamPipeS1Vacuum", fieldOfSolenoidFieldS1, false);
            RegisterField(solenoidBeamPipeT1, "SolenoidBeamPipeT1Vacuum", fieldOfSolenoidFieldT1, false);
            RegisterField(solenoidBeamPipeS2, "SolenoidBeamPipeS2Vacuum", fieldOfSolenoidFieldS2, false);
            RegisterField(solenoidBeamPipeT2, "SolenoidBeamPipeT2Vacuum", fieldOfSolenoidFieldT2, false);
            RegisterField(solenoidBeamPipeS3, "SolenoidBeamPipeS3Vacuum", fieldOfSolenoidFieldS3, false);
            RegisterField(mcpChamber, "MCPChamberPipeVacuum", fieldOfEMCField, false);
            RegisterField(mcpChamber, "MCPChamberVacuum", fieldOfEMCField, false);
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

} // namespace MACE::SimPTS::inline Action
