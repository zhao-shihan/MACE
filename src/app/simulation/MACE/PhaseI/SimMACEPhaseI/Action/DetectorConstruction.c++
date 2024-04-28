#include "MACE/Detector/Definition/DefinitionBase.h++"
#include "MACE/Detector/Definition/EMCCrystal.h++"
#include "MACE/Detector/Definition/EMCPMTAssemblies.h++"
#include "MACE/Detector/Definition/MCPChamber.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Action/DetectorConstruction.h++"
#include "MACE/PhaseI/SimMACEPhaseI/Messenger/DetectorMessenger.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/EMCPMTSD.h++"
#include "MACE/PhaseI/SimMACEPhaseI/SD/EMCSD.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <array>

namespace MACE::PhaseI::SimMACEPhaseI::inline Action {

using namespace LiteralUnit;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{},
    fDefaultGaseousRegion{},
    fDefaultSolidRegion{},
    fEMCSensitiveRegion{},
    fShieldRegion{},
    fTargetRegion{},
    fVacuumRegion{},
    fEMCSD{},
    fEMCPMTSD{} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace Detector::Definition;

    fWorld = std::make_unique<World>();
    auto& emcCrystal{fWorld->NewDaughter<EMCCrystal>(fCheckOverlap)};
    auto& emcPMTAssemblies{fWorld->NewDaughter<EMCPMTAssemblies>(fCheckOverlap)};
    /* auto& mcpChamber = */ fWorld->NewDaughter<MCPChamber>(fCheckOverlap);

    const auto nist{G4NistManager::Instance()};
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3));

    const auto defaultCuts{G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts()};

    fEMCSensitiveRegion = new Region("EMCSensitive", RegionType::EMCSensitive);
    fEMCSensitiveRegion->SetProductionCuts(defaultCuts);
    emcCrystal.RegisterRegion(fEMCSensitiveRegion);

    fShieldRegion = new Region("Shield", RegionType::Shield);
    fShieldRegion->SetProductionCuts(defaultCuts);

    const auto& emcName{MACE::Detector::Description::EMC::Instance().Name()};

    fEMCPMTSD = new SD::EMCPMTSD{emcName + "PMT"};
    emcPMTAssemblies.RegisterSD("EMCPMTCathode", fEMCPMTSD);

    fEMCSD = new SD::EMCSD{emcName, fEMCPMTSD};
    emcCrystal.RegisterSD(fEMCSD);

    return fWorld->PhysicalVolume();
}

} // namespace MACE::PhaseI::SimMACEPhaseI::inline Action
