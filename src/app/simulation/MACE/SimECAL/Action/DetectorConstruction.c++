#include "MACE/Detector/Definition/ECALCrystal.h++"
#include "MACE/Detector/Definition/ECALPhotoSensor.h++"
#include "MACE/Detector/Definition/ECALPhotoSensor.h++"
#include "MACE/Detector/Definition/MCP.h++"
#include "MACE/Detector/Definition/MCPChamber.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/ECAL.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/SimECAL/Action/DetectorConstruction.h++"
#include "MACE/SimECAL/Detector/ECALMagnet.h++"
#include "MACE/SimECAL/Detector/ECALShield.h++"
#include "MACE/SimECAL/Detector/ECALTunnel.h++"
#include "MACE/SimECAL/Messenger/DetectorMessenger.h++"
#include "MACE/SimECAL/SD/ECALPMSD.h++"
#include "MACE/SimECAL/SD/ECALSD.h++"
#include "MACE/SimECAL/SD/MCPSD.h++"

#include "Mustard/Detector/Definition/DefinitionBase.h++"
#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "G4ProductionCuts.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <array>

namespace MACE::SimECAL::inline Action {

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
    auto& ecalCrystal{fWorld->NewDaughter<ECALCrystal>(fCheckOverlap)};
    auto& ecalPhotoSensor{fWorld->NewDaughter<ECALPhotoSensor>(fCheckOverlap)};
    // auto& mcpChamber{fWorld->NewDaughter<MCPChamber>(fCheckOverlap)};
    // auto& ecalMagnet = fWorld->NewDaughter<SimECAL::Detector::ECALMagnet>(fCheckOverlap);
    // auto& ecalShield = fWorld->NewDaughter<SimECAL::Detector::ECALShield>(fCheckOverlap);

    // auto& ecalTunnel = fWorld->NewDaughter<SimECAL::Detector::ECALTunnel>(fCheckOverlap);

    // auto& mcp{mcpChamber.NewDaughter<MCP>(fCheckOverlap)};

    // Shield region

    // const auto shieldRegionCut{new G4ProductionCuts};
    // shieldRegionCut->SetProductionCut(2_mm);
    // const auto shieldRegion{new G4Region{"Shield"}};
    // shieldRegion->SetProductionCuts(shieldRegionCut);

    // ecalShield.RegisterRegion(shieldRegion);

    const auto& ecalName{MACE::Detector::Description::ECAL::Instance().Name()};
    std::cout <<"ECALname got."<<"\n";
    const auto ecalPMSD{new SD::ECALPMSD{ecalName + "PM"}};
    std::cout <<"PMSD instance completed."<<"\n";
    ecalCrystal.RegisterSD(new SD::ECALSD{ecalName, ecalPMSD});
    std::cout <<"crystalSD register completed."<<"\n";

    ecalPhotoSensor.RegisterSD("ECALPMCathode", ecalPMSD);
    std::cout <<"PMSD register completed."<<"\n";


    // mcp.RegisterSD(new SD::MCPSD{MACE::Detector::Description::MCP::Instance().Name()});

    // fWorld->ParallelExport("ECALPhaseII.gdml");

    return fWorld->PhysicalVolume();
    std::cout <<"Detector Construction completed."<<"\n";
}

} // namespace MACE::SimECAL::inline Action
