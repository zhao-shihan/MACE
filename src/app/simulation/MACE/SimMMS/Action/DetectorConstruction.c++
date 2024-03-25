#include "MACE/Detector/Definition/CDCBody.h++"
#include "MACE/Detector/Definition/CDCCell.h++"
#include "MACE/Detector/Definition/CDCGas.h++"
#include "MACE/Detector/Definition/CDCSenseLayer.h++"
#include "MACE/Detector/Definition/CDCSuperLayer.h++"
#include "MACE/Detector/Definition/DefinitionBase.h++"
#include "MACE/Detector/Definition/Filter.h++"
#include "MACE/Detector/Definition/MMSBeamPipe.h++"
#include "MACE/Detector/Definition/MMSField.h++"
#include "MACE/Detector/Definition/MMSMagnet.h++"
#include "MACE/Detector/Definition/MMSShield.h++"
#include "MACE/Detector/Definition/STC.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/CDC.h++"
#include "MACE/SimMMS/Action/DetectorConstruction.h++"
#include "MACE/SimMMS/Messenger/DetectorMessenger.h++"
#include "MACE/SimMMS/SD/CDCSD.h++"
#include "MACE/SimMMS/SD/STCSD.h++"
#include "MACE/Simulation/Field/AcceleratorField.h++"
#include "MACE/Simulation/Field/MMSField.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4EqMagElectricField.hh"
#include "G4InterpolationDriver.hh"
#include "G4NistManager.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

namespace MACE::SimMMS::inline Action {

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
    fShieldRegion{},
    fSolenoidOrMagnetRegion{},
    fSTCSensitiveRegion{},
    fTargetRegion{},
    fVacuumRegion{},
    fCDCSD{},
    fSTCSD{} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    // 0

    fWorld = std::make_unique<Detector::Definition::World>();

    // 1

    auto& mmsField{fWorld->NewDaughter<Detector::Definition::MMSField>(fCheckOverlap)};
    auto& mmsShield{fWorld->NewDaughter<Detector::Definition::MMSShield>(fCheckOverlap)};

    // 2

    auto& cdcBody{mmsField.NewDaughter<Detector::Definition::CDCBody>(fCheckOverlap)};
    auto& mmsBeamPipe{mmsField.NewDaughter<Detector::Definition::MMSBeamPipe>(fCheckOverlap)};
    auto& mmsMagnet{mmsField.NewDaughter<Detector::Definition::MMSMagnet>(fCheckOverlap)};
    auto& stc{mmsField.NewDaughter<Detector::Definition::STC>(fCheckOverlap)};

    // 3

    auto& cdcGas{cdcBody.NewDaughter<Detector::Definition::CDCGas>(fCheckOverlap)};

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
        using namespace MACE::LiteralUnit::Density;

        const auto nist = G4NistManager::Instance();

        const auto vacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3);
        mmsField.RegisterMaterial(vacuum);
        fWorld->RegisterMaterial(vacuum);
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

        cdcBody.RegisterRegion(fDefaultSolidRegion);
        mmsBeamPipe.RegisterRegion(fDefaultSolidRegion);

        // ShieldRegion
        fShieldRegion = new Region("Shield", RegionType::Shield);
        fShieldRegion->SetProductionCuts(defaultCuts);

        mmsShield.RegisterRegion(fShieldRegion);

        // SolenoidOrMagnetRegion
        fSolenoidOrMagnetRegion = new Region("SolenoidOrMagnet", RegionType::SolenoidOrMagnet);
        fSolenoidOrMagnetRegion->SetProductionCuts(defaultCuts);

        mmsMagnet.RegisterRegion(fSolenoidOrMagnetRegion);

        // CDCSensitiveRegion
        fCDCSensitiveRegion = new Region("CDCSensitive", RegionType::CDCSensitive);
        fCDCSensitiveRegion->SetProductionCuts(defaultCuts);

        cdcCell.RegisterRegion("CDCSensitiveVolume", fCDCSensitiveRegion);

        // STCSensitiveRegionRegion
        fSTCSensitiveRegion = new Region("STCSensitiveRegion", RegionType::STCSensitive);
        fSTCSensitiveRegion->SetProductionCuts(defaultCuts);

        stc.RegisterRegion(fSTCSensitiveRegion);

        // VacuumRegion
        fVacuumRegion = new Region("Vacuum", RegionType::Vacuum);
        fVacuumRegion->SetProductionCuts(defaultCuts);

        mmsField.RegisterRegion(fVacuumRegion);
    }

    ////////////////////////////////////////////////////////////////
    // Register SDs
    ////////////////////////////////////////////////////////////////
    {
        fCDCSD = new SD::CDCSD{Detector::Description::CDC::Instance().Name()};
        cdcCell.RegisterSD("CDCSensitiveVolume", fCDCSD);

        fSTCSD = new SD::STCSD{Detector::Description::STC::Instance().Name()};
        stc.RegisterSD(fSTCSD);
    }

    ////////////////////////////////////////////////////////////////
    // Register background fields
    ////////////////////////////////////////////////////////////////
    {
        using namespace LiteralUnit::Length;
        using namespace LiteralUnit::MagneticFluxDensity;

        constexpr auto hMin = 100_um;

        mmsField.RegisterField<
            MMSField,
            G4TMagFieldEquation<MMSField>,
            G4TDormandPrince45<G4TMagFieldEquation<MMSField>>,
            G4InterpolationDriver<G4TDormandPrince45<G4TMagFieldEquation<MMSField>>>>(
            new MMSField, hMin, 6, 6, false);
    }

    return fWorld->PhysicalVolume();
}

} // namespace MACE::SimMMS::inline Action
