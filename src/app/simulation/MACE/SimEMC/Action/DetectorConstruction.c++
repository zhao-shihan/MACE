#include "MACE/Detector/Definition/EMCCrystal.h++"
#include "MACE/Detector/Definition/EMCMPPC.h++"
#include "MACE/Detector/Definition/EMCPMTAssemblies.h++"
#include "MACE/Detector/Definition/MCP.h++"
#include "MACE/Detector/Definition/MCPChamber.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/SimEMC/Detector/EMCMagnet.h++"
#include "MACE/SimEMC/Detector/EMCShield.h++"
#include "MACE/SimEMC/Detector/EMCTunnel.h++"
#include "MACE/SimEMC/Messenger/DetectorMessenger.h++"
#include "MACE/SimEMC/SD/EMCPMTSD.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"
#include "MACE/SimEMC/SD/MCPSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <array>

namespace MACE::SimEMC::inline Action {

using namespace Mustard::LiteralUnit;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{} {
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace MACE::Detector::Definition;

    // auto& description = MACE::Detector::Description::World::Instance();
    // description.HalfXExtent(26_m);
    // description.HalfYExtent(20_m);
    // description.HalfZExtent(26_m);

    fWorld = std::make_unique<World>();
    auto& emcCrystal{fWorld->NewDaughter<EMCCrystal>(fCheckOverlap)};
    auto& emcPMTAssemblies{fWorld->NewDaughter<EMCPMTAssemblies>(fCheckOverlap)};
    auto& mcpChamber{fWorld->NewDaughter<MCPChamber>(fCheckOverlap)};

    auto& emcMagnet = fWorld->NewDaughter<SimEMC::Detector::EMCMagnet>(fCheckOverlap);
    auto& emcShield = fWorld->NewDaughter<SimEMC::Detector::EMCShield>(fCheckOverlap);
    // auto& emcTunnel = fWorld->NewDaughter<SimEMC::Detector::EMCTunnel>(fCheckOverlap);

    auto& mcp{mcpChamber.NewDaughter<MCP>(fCheckOverlap)};

    // Shield region

    const auto shieldRegionCut{new G4ProductionCuts};
    shieldRegionCut->SetProductionCut(2_mm);
    const auto shieldRegion{new G4Region{"Shield"}};
    shieldRegion->SetProductionCuts(shieldRegionCut);

    emcShield.RegisterRegion(shieldRegion);

    const auto& emcName{MACE::Detector::Description::EMC::Instance().Name()};
    const auto emcPMTSD{new SD::EMCPMTSD{emcName + "PMT"}};
    emcPMTAssemblies.RegisterSD("EMCPMTCathode", emcPMTSD);
    emcCrystal.RegisterSD(new SD::EMCSD{emcName, emcPMTSD});

    // mcp.RegisterSD(new SD::MCPSD{MACE::Detector::Description::MCP::Instance().Name()});

    // fWorld->ParallelExport("EMCPhaseII.gdml");

    return fWorld->PhysicalVolume();
}

} // namespace MACE::SimEMC::inline Action
