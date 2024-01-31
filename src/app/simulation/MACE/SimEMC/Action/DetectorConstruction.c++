#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Description/EMC.h++"
#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Detector/Description/World.h++"
#include "MACE/Detector/Geometry/Fast/EMCCrystal.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTAssemblies.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTCoupler.h++"
#include "MACE/Detector/Geometry/Fast/MCP.h++"
#include "MACE/Detector/Geometry/Fast/World.h++"
#include "MACE/Detector/Geometry/GeometryBase.h++"
#include "MACE/SimEMC/Action/DetectorConstruction.h++"
#include "MACE/SimEMC/Detector/EMCShield.h++"
#include "MACE/SimEMC/Detector/EMCTunnel.h++"
#include "MACE/SimEMC/Messenger/DetectorMessenger.h++"
#include "MACE/SimEMC/SD/EMCPMTSD.h++"
#include "MACE/SimEMC/SD/EMCSD.h++"
#include "MACE/SimEMC/SD/MCPSD.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "G4NistManager.hh"
#include "G4ProductionCuts.hh"
#include "G4ProductionCutsTable.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

#include <array>

namespace MACE::SimEMC::inline Action {

using namespace LiteralUnit;

DetectorConstruction::DetectorConstruction() :
    PassiveSingleton{},
    G4VUserDetectorConstruction{},
    fCheckOverlap{false},
    fWorld{},
    fEMCSensitiveRegion{},
    fMCPSensitiveRegion{},
    fShieldRegion{},
    fTunnelRegion{},
    fVacuumRegion{},

    fEMCSD{},
    fEMCPMTSD{} {
    // Detector::Description::DescriptionIO::Import<DescriptionInUse>(
    // #include "MACE/SimEMC/DefaultGeometry.inlyaml"
    // );
    // GeometryMessenger::Instance().Register(this);
    DetectorMessenger::EnsureInstantiation();
}

auto DetectorConstruction::Construct() -> G4VPhysicalVolume* {
    using namespace MACE::Detector::Geometry::Fast;

    auto& description = MACE::Detector::Description::World::Instance();
    description.HalfXExtent(26_m);
    description.HalfYExtent(20_m);
    description.HalfZExtent(26_m);

    fWorld = std::make_unique<World>();
    auto& emcCrystal = fWorld->NewDaughter<EMCCrystal>(fCheckOverlap);
    fWorld->NewDaughter<EMCPMTCoupler>(fCheckOverlap);
    auto& emcPMTAssemblies = fWorld->NewDaughter<EMCPMTAssemblies>(fCheckOverlap);
    auto& mcp = fWorld->NewDaughter<MCP>(fCheckOverlap);
    // auto& emcShield = fWorld->NewDaughter<SimEMC::Detector::EMCShield>(fCheckOverlap);
    // auto& emcTunnel = fWorld->NewDaughter<SimEMC::Detector::EMCTunnel>(fCheckOverlap);

    auto nist = G4NistManager::Instance();
    fWorld->RegisterMaterial(nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3));

    const auto defaultCuts = G4ProductionCutsTable::GetProductionCutsTable()->GetDefaultProductionCuts();

    fEMCSensitiveRegion = new Region("EMCSensitive", RegionType::EMCSensitive);
    fEMCSensitiveRegion->SetProductionCuts(defaultCuts);

    emcCrystal.RegisterRegion(fEMCSensitiveRegion);

    fMCPSensitiveRegion = new Region("MCPSensitive", RegionType::MCPSensitive);
    fMCPSensitiveRegion->SetProductionCuts(defaultCuts);

    mcp.RegisterRegion(fMCPSensitiveRegion);

    // fShieldRegion = new Region("Shield", RegionType::Shield);
    // fShieldRegion->SetProductionCuts(defaultCuts);

    // emcShield.RegisterRegion(fShieldRegion);

    // fTunnelRegion = new Region("Tunnel", RegionType::Tunnel);
    // const auto cuts = new G4ProductionCuts;
    // cuts->SetProductionCut(2.5_cm);
    // fTunnelRegion->SetProductionCuts(cuts);

    // emcTunnel.RegisterRegion(fTunnelRegion);

    const auto& emcName{MACE::Detector::Description::EMC::Instance().Name()};

    fEMCPMTSD = new SD::EMCPMTSD{emcName + "PMT"};
    emcPMTAssemblies.RegisterSD("EMCPMTCathode", fEMCPMTSD);

    fEMCSD = new SD::EMCSD{emcName, fEMCPMTSD};
    emcCrystal.RegisterSD(fEMCSD);

    fMCPSD = new SD::MCPSD{MACE::Detector::Description::MCP::Instance().Name()};
    mcp.RegisterSD(fMCPSD);

    // fWorld->Export("geometry.gdml");

    return fWorld->PhysicalVolume().get();
}

} // namespace MACE::SimEMC::inline Action
