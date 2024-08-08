#include "MACE/Detector/Definition/ECalCrystal.h++"
#include "MACE/Detector/Definition/ECalPMTAssemblies.h++"
#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Description/ECal.h++"
#include "MACE/PhaseI/Detector/Definition/CentralBeamPipe.h++"
#include "MACE/PhaseI/Detector/Definition/World.h++"
#include "MACE/PhaseI/Detector/Description/UsePhaseIDefault.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/DetectorConstruction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Messenger/DetectorMessenger.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECalPMTSD.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/ECalSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <array>

namespace MACE::PhaseI::SimMACEPhaseI::inline Action {

using namespace Mustard::LiteralUnit;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{},
    fDefaultGaseousRegion{},
    fDefaultSolidRegion{},
    fECalSensitiveRegion{},
    fShieldRegion{},
    fTargetRegion{},
    fVacuumRegion{},
    fECalSD{},
    fECalPMTSD{} {
    DetectorMessenger::EnsureInstantiation();
    Detector::Description::UsePhaseIDefault();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    namespace PhaseI = PhaseI::Detector::Definition;
    using namespace MACE::Detector::Definition;

    fWorld = std::make_unique<PhaseI::World>();
    auto& eCalCrystal{fWorld->NewDaughter<ECalCrystal>(fCheckOverlap)};
    auto& eCalPMTAssemblies{fWorld->NewDaughter<ECalPMTAssemblies>(fCheckOverlap)};
    auto& centralBeamPipe{fWorld->NewDaughter<PhaseI::CentralBeamPipe>(fCheckOverlap)};

    auto& target{centralBeamPipe.NewDaughter<Target>(fCheckOverlap)};

    const auto defaultCuts{G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts()};

    fECalSensitiveRegion = new Region{"ECalSensitive", RegionType::ECalSensitive};
    fECalSensitiveRegion->SetProductionCuts(defaultCuts);
    eCalCrystal.RegisterRegion(fECalSensitiveRegion);

    fDefaultSolidRegion = new Region{"DefaultSolid", RegionType::DefaultSolid};
    fDefaultSolidRegion->SetProductionCuts(defaultCuts);
    centralBeamPipe.RegisterRegion(fDefaultSolidRegion);

    fTargetRegion = new Region{"Target", RegionType::Target};
    fTargetRegion->SetProductionCuts(defaultCuts);
    target.RegisterRegion(fTargetRegion);

    const auto& eCalName{MACE::Detector::Description::ECal::Instance().Name()};

    fECalPMTSD = new SD::ECalPMTSD{eCalName + "PMT"};
    eCalPMTAssemblies.RegisterSD("ECalPMTCathode", fECalPMTSD);

    fECalSD = new SD::ECalSD{eCalName, fECalPMTSD};
    eCalCrystal.RegisterSD(fECalSD);

    return fWorld->PhysicalVolume();
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Action
