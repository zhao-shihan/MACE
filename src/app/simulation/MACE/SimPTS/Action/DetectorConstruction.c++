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
#include "G4NistManager.hh"
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
    fMinDriverStep{0.5_um},
    fDeltaChord{5_um},
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
    auto& virtualDetectorD{emcField.NewDaughter<Detector::Definition::VirtualDetectorD>(fCheckOverlap)};

    auto& solenoidBeamPipeS1{solenoidFieldS1.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeS1>(fCheckOverlap)};
    auto& solenoidS1{solenoidFieldS1.NewDaughter<MACE::Detector::Definition::SolenoidS1>(fCheckOverlap)};
    auto& solenoidShieldS1{solenoidFieldS1.NewDaughter<MACE::Detector::Definition::SolenoidShieldS1>(fCheckOverlap)};

    auto& filter{solenoidFieldS2.NewDaughter<MACE::Detector::Definition::Filter>(fCheckOverlap)};
    auto& solenoidBeamPipeS2{solenoidFieldS2.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeS2>(fCheckOverlap)};
    auto& solenoidS2{solenoidFieldS2.NewDaughter<MACE::Detector::Definition::SolenoidS2>(fCheckOverlap)};
    auto& solenoidShieldS2{solenoidFieldS2.NewDaughter<MACE::Detector::Definition::SolenoidShieldS2>(fCheckOverlap)};
    auto& virtualDetectorB{solenoidFieldS2.NewDaughter<Detector::Definition::VirtualDetectorB>(fCheckOverlap)};
    auto& virtualDetectorC{solenoidFieldS2.NewDaughter<Detector::Definition::VirtualDetectorC>(fCheckOverlap)};

    auto& solenoidBeamPipeS3{solenoidFieldS3.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeS3>(fCheckOverlap)};
    auto& solenoidS3{solenoidFieldS3.NewDaughter<MACE::Detector::Definition::SolenoidS3>(fCheckOverlap)};
    auto& solenoidShieldS3{solenoidFieldS3.NewDaughter<MACE::Detector::Definition::SolenoidShieldS3>(fCheckOverlap)};

    auto& solenoidBeamPipeT1{solenoidFieldT1.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeT1>(fCheckOverlap)};
    auto& solenoidShieldT1{solenoidFieldT1.NewDaughter<MACE::Detector::Definition::SolenoidShieldT1>(fCheckOverlap)};
    auto& solenoidT1{solenoidFieldT1.NewDaughter<MACE::Detector::Definition::SolenoidT1>(fCheckOverlap)};

    auto& solenoidBeamPipeT2{solenoidFieldT2.NewDaughter<MACE::Detector::Definition::SolenoidBeamPipeT2>(fCheckOverlap)};
    auto& solenoidShieldT2{solenoidFieldT2.NewDaughter<MACE::Detector::Definition::SolenoidShieldT2>(fCheckOverlap)};
    auto& solenoidT2{solenoidFieldT2.NewDaughter<MACE::Detector::Definition::SolenoidT2>(fCheckOverlap)};

    auto& acceleratorField{mmsField.NewDaughter<MACE::Detector::Definition::AcceleratorField>(fCheckOverlap)};
    auto& mmsBeamPipe{mmsField.NewDaughter<MACE::Detector::Definition::MMSBeamPipe>(fCheckOverlap)};
    auto& mmsMagnet{mmsField.NewDaughter<MACE::Detector::Definition::MMSMagnet>(fCheckOverlap)};
    auto& virtualDetectorA{mmsField.NewDaughter<Detector::Definition::VirtualDetectorA>(fCheckOverlap)};

    // 3

    auto& accelerator{acceleratorField.NewDaughter<MACE::Detector::Definition::Accelerator>(fCheckOverlap)};

    ////////////////////////////////////////////////////////////////
    // Register materials
    ////////////////////////////////////////////////////////////////
    {
        using namespace Mustard::LiteralUnit::Density;

        const auto nist{G4NistManager::Instance()};

        const auto vacuum{nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3)};
        acceleratorField.RegisterMaterial(vacuum);
        emcField.RegisterMaterial(vacuum);
        fWorld->RegisterMaterial(vacuum);
        mmsField.RegisterMaterial(vacuum);
        solenoidFieldS1.RegisterMaterial(vacuum);
        solenoidFieldS2.RegisterMaterial(vacuum);
        solenoidFieldS3.RegisterMaterial(vacuum);
        solenoidFieldT1.RegisterMaterial(vacuum);
        solenoidFieldT2.RegisterMaterial(vacuum);
        virtualDetectorA.RegisterMaterial(vacuum);
        virtualDetectorB.RegisterMaterial(vacuum);
        virtualDetectorC.RegisterMaterial(vacuum);
        virtualDetectorD.RegisterMaterial(vacuum);
    }

    ////////////////////////////////////////////////////////////////
    // Register regions
    ////////////////////////////////////////////////////////////////
    {
        const auto defaultCuts{G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts()};

        // DefaultGaseousRegion
        fDefaultGaseousRegion = new Region("DefaultGaseous", RegionType::DefaultGaseous);
        fDefaultGaseousRegion->SetProductionCuts(defaultCuts);

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
        using namespace Mustard::LiteralUnit::MagneticFluxDensity;

        { // magnetic field in gas
            using Field = Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::MMSField>;
            using Equation = G4TMagFieldEquation<Field>;
            using Stepper = G4TDormandPrince45<Equation, 6>;
            using Driver = G4InterpolationDriver<Stepper>;
            const auto field{new Field};
            const auto equation{new Equation{field}}; // clang-format off
            const auto stepper{new Stepper{equation, 6}};
            const auto driver{new Driver{fMinDriverStep, stepper, 6}}; // clang-format on
            const auto chordFinder{new G4ChordFinder{driver}};
            chordFinder->SetDeltaChord(fDeltaChord);
            mmsField.RegisterField(std::make_unique<G4FieldManager>(field, chordFinder), false);
        }
        { // magnetic field in vacuum
            const auto RegisterMagneticField{
                [this]<typename AField>(Mustard::Detector::Definition::DefinitionBase& detector, AField* field, bool forceToAllDaughters) {
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
                    detector.RegisterField(std::make_unique<G4FieldManager>(field, chordFinder), forceToAllDaughters);
                }};
            RegisterMagneticField(solenoidFieldS1, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldS1>, false);
            RegisterMagneticField(solenoidFieldT1, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldT1>, false);
            RegisterMagneticField(solenoidFieldS2, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldS2>, false);
            RegisterMagneticField(solenoidFieldT2, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldT2>, false);
            RegisterMagneticField(solenoidFieldS3, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::SolenoidFieldS3>, false);
            RegisterMagneticField(emcField, new Mustard::Detector::Field::AsG4Field<MACE::Detector::Field::EMCField>, false);
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
