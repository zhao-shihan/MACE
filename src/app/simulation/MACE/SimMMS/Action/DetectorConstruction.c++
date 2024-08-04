#include "MACE/Detector/Assembly/MMS.h++"
#include "MACE/Detector/Definition/CDCBody.h++"
#include "MACE/Detector/Definition/CDCCell.h++"
#include "MACE/Detector/Definition/CDCGas.h++"
#include "MACE/Detector/Definition/CDCSenseLayer.h++"
#include "MACE/Detector/Definition/CDCSuperLayer.h++"
#include "MACE/Detector/Definition/MMSBeamPipe.h++"
#include "MACE/Detector/Definition/MMSField.h++"
#include "MACE/Detector/Definition/MMSMagnet.h++"
#include "MACE/Detector/Definition/MMSShield.h++"
#include "MACE/Detector/Definition/TTC.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Field/MMSField.h++"
#include "MACE/SimMMS/Action/DetectorConstruction.h++"
#include "MACE/SimMMS/Messenger/DetectorMessenger.h++"
#include "MACE/SimMMS/SD/CDCSD.h++"
#include "MACE/SimMMS/SD/TTCSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Field/AsG4Field.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4ChordFinder.hh"
#include "G4InterpolationDriver.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4TDormandPrince45.hh"
#include "G4TMagFieldEquation.hh"

namespace MACE::SimMMS::inline Action {

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
    fShieldRegion{},
    fSolenoidOrMagnetRegion{},
    fTTCSensitiveRegion{},
    fTargetRegion{},
    fVacuumRegion{},
    fCDCSD{},
    fTTCSD{},
    fNumericMessengerRegister{this} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    fWorld = std::make_unique<Detector::Definition::World>();
    Detector::Assembly::MMS mms{*fWorld, fCheckOverlap};

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
        mms.Get<Detector::Definition::MMSField>().RegisterRegion(fDefaultGaseousRegion);

        // DefaultSolidRegion
        fDefaultSolidRegion = new Region("DefaultSolid", RegionType::DefaultSolid);
        fDefaultSolidRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::CDCBody>().RegisterRegion(fDefaultSolidRegion);
        mms.Get<Detector::Definition::MMSBeamPipe>().RegisterRegion(fDefaultSolidRegion);

        // ShieldRegion
        fShieldRegion = new Region("Shield", RegionType::Shield);
        fShieldRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::MMSShield>().RegisterRegion(fShieldRegion);

        // SolenoidOrMagnetRegion
        fSolenoidOrMagnetRegion = new Region("SolenoidOrMagnet", RegionType::SolenoidOrMagnet);
        fSolenoidOrMagnetRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::MMSMagnet>().RegisterRegion(fSolenoidOrMagnetRegion);

        // CDCSensitiveRegion
        fCDCSensitiveRegion = new Region("CDCSensitive", RegionType::CDCSensitive);
        fCDCSensitiveRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::CDCCell>().RegisterRegion("CDCSensitiveVolume", fCDCSensitiveRegion);

        // TTCSensitiveRegionRegion
        fTTCSensitiveRegion = new Region("TTCSensitiveRegion", RegionType::TTCSensitive);
        fTTCSensitiveRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::TTC>().RegisterRegion(fTTCSensitiveRegion);

        // VacuumRegion
        fVacuumRegion = new Region("Vacuum", RegionType::Vacuum);
        fVacuumRegion->SetProductionCuts(defaultCuts);

        mms.Get<Detector::Definition::MMSBeamPipe>().RegisterRegion("MMSBeamPipeVacuum", fVacuumRegion);
    }

    ////////////////////////////////////////////////////////////////
    // Register SDs
    ////////////////////////////////////////////////////////////////
    {
        fCDCSD = new SD::CDCSD{Detector::Description::CDC::Instance().Name()};
        mms.Get<Detector::Definition::CDCCell>().RegisterSD("CDCSensitiveVolume", fCDCSD);

        fTTCSD = new SD::TTCSD{Detector::Description::TTC::Instance().Name()};
        mms.Get<Detector::Definition::TTC>().RegisterSD(fTTCSD);
    }

    ////////////////////////////////////////////////////////////////
    // Register background fields
    ////////////////////////////////////////////////////////////////
    {
        using Field = Mustard::Detector::Field::AsG4Field<Detector::Field::MMSField>;
        using Equation = G4TMagFieldEquation<Field>;
        using Stepper = G4TDormandPrince45<Equation, 6>;
        using Driver = G4InterpolationDriver<Stepper>;
        const auto field{new Field};
        const auto equation{new Equation{field}}; // clang-format off
        const auto stepper{new Stepper{equation, 6}};
        const auto driver{new Driver{fMinDriverStep, stepper, 6}}; // clang-format on
        const auto chordFinder{new G4ChordFinder{driver}};
        chordFinder->SetDeltaChord(fDeltaChord);
        mms.Get<Detector::Definition::MMSField>().RegisterField(std::make_unique<G4FieldManager>(field, chordFinder), false);
    }

    return fWorld->PhysicalVolume();
}

} // namespace MACE::SimMMS::inline Action
