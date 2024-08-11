#include "MACE/Detector/Definition/ECalCrystal.h++"
#include "MACE/Detector/Definition/ECalMPPC.h++"
#include "MACE/Detector/Definition/ECalPMTAssemblies.h++"
#include "MACE/Detector/Definition/MCP.h++"
#include "MACE/Detector/Definition/MCPChamber.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/ECal.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/SimECal/Action/DetectorConstruction.h++"
#include "MACE/SimECal/Detector/ECalMagnet.h++"
#include "MACE/SimECal/Detector/ECalShield.h++"
#include "MACE/SimECal/Detector/ECalTunnel.h++"
#include "MACE/SimECal/Messenger/DetectorMessenger.h++"
#include "MACE/SimECal/SD/ECalPMTSD.h++"
#include "MACE/SimECal/SD/ECalSD.h++"
#include "MACE/SimECal/SD/MCPSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <array>

namespace MACE::SimECal::inline Action {

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
    auto& eCalCrystal{fWorld->NewDaughter<ECalCrystal>(fCheckOverlap)};
    auto& eCalPMTAssemblies{fWorld->NewDaughter<ECalPMTAssemblies>(fCheckOverlap)};
    auto& mcpChamber{fWorld->NewDaughter<MCPChamber>(fCheckOverlap)};

    auto& eCalMagnet = fWorld->NewDaughter<SimECal::Detector::ECalMagnet>(fCheckOverlap);
    auto& eCalShield = fWorld->NewDaughter<SimECal::Detector::ECalShield>(fCheckOverlap);
    // auto& eCalTunnel = fWorld->NewDaughter<SimECal::Detector::ECalTunnel>(fCheckOverlap);

    auto& mcp{mcpChamber.NewDaughter<MCP>(fCheckOverlap)};

    // Shield region

    const auto shieldRegionCut{new G4ProductionCuts};
    shieldRegionCut->SetProductionCut(2_mm);
    const auto shieldRegion{new G4Region{"Shield"}};
    shieldRegion->SetProductionCuts(shieldRegionCut);

    eCalShield.RegisterRegion(shieldRegion);

    const auto& eCalName{MACE::Detector::Description::ECal::Instance().Name()};
    const auto eCalPMTSD{new SD::ECalPMTSD{eCalName + "PMT"}};
    eCalPMTAssemblies.RegisterSD("ECalPMTCathode", eCalPMTSD);
    eCalCrystal.RegisterSD(new SD::ECalSD{eCalName, eCalPMTSD});

    // mcp.RegisterSD(new SD::MCPSD{MACE::Detector::Description::MCP::Instance().Name()});

    // fWorld->ParallelExport("ECalPhaseII.gdml");

    return fWorld->PhysicalVolume();
}

} // namespace MACE::SimECal::inline Action
