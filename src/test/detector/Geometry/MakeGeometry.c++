#include "MACE/Detector/Definition/Accelerator.h++"
#include "MACE/Detector/Definition/AcceleratorField.h++"
#include "MACE/Detector/Definition/BeamDegrader.h++"
#include "MACE/Detector/Definition/BeamMonitor.h++"
#include "MACE/Detector/Definition/CDCBody.h++"
#include "MACE/Detector/Definition/CDCCell.h++"
#include "MACE/Detector/Definition/CDCGas.h++"
#include "MACE/Detector/Definition/CDCSenseLayer.h++"
#include "MACE/Detector/Definition/CDCSuperLayer.h++"
#include "MACE/Detector/Definition/EMCCrystal.h++"
#include "MACE/Detector/Definition/EMCField.h++"
#include "MACE/Detector/Definition/EMCMagnet.h++"
#include "MACE/Detector/Definition/EMCPMTAssemblies.h++"
#include "MACE/Detector/Definition/EMCShield.h++"
#include "MACE/Detector/Definition/Filter.h++"
#include "MACE/Detector/Definition/MCP.h++"
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
#include "MACE/Detector/Definition/TTC.h++"
#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Definition/World.h++"

#include "Mustard/Detector/Description/DescriptionIO.h++"
#include "Mustard/Env/BasicEnv.h++"
#include "Mustard/Env/CLI/BasicCLI.h++"
#include "Mustard/Utility/LiteralUnit.h++"

#include "TGeoManager.h"

#include "G4NistManager.hh"

#include <functional>

int main(int argc, char* argv[]) {
    Mustard::Env::CLI::BasicCLI cli;
    Mustard::Env::BasicEnv env(argc, argv, cli);

    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    using namespace MACE::Detector::Definition;

    constexpr auto fCheckOverlap = true;

    // 0

    const auto fWorld = std::make_unique_for_overwrite<World>();

    // 1

    auto& emcField{fWorld->NewDaughter<EMCField>(fCheckOverlap)};
    /* auto& emcShield */ fWorld->NewDaughter<EMCShield>(fCheckOverlap);
    auto& mmsField{fWorld->NewDaughter<MMSField>(fCheckOverlap)};
    /* auto& mmsShield */ fWorld->NewDaughter<MMSShield>(fCheckOverlap);
    /* auto& shieldingWall */ fWorld->NewDaughter<ShieldingWall>(fCheckOverlap);
    auto& solenoidFieldS1{fWorld->NewDaughter<SolenoidFieldS1>(fCheckOverlap)};
    auto& solenoidFieldS2{fWorld->NewDaughter<SolenoidFieldS2>(fCheckOverlap)};
    auto& solenoidFieldS3{fWorld->NewDaughter<SolenoidFieldS3>(fCheckOverlap)};
    auto& solenoidFieldT1{fWorld->NewDaughter<SolenoidFieldT1>(fCheckOverlap)};
    auto& solenoidFieldT2{fWorld->NewDaughter<SolenoidFieldT2>(fCheckOverlap)};

    // 2

    /* auto& emcCrystal */ emcField.NewDaughter<EMCCrystal>(fCheckOverlap);
    /* auto& emcMagnet */ emcField.NewDaughter<EMCMagnet>(fCheckOverlap);
    /* auto& emcPMTAssemblies */ emcField.NewDaughter<EMCPMTAssemblies>(fCheckOverlap);
    /* auto& mcp */ emcField.NewDaughter<MCP>(fCheckOverlap);
    /* auto& mcpChamber */ emcField.NewDaughter<MCPChamber>(fCheckOverlap);

    auto& acceleratorField{mmsField.NewDaughter<AcceleratorField>(fCheckOverlap)};
    auto& cdcBody{mmsField.NewDaughter<CDCBody>(fCheckOverlap)};
    /* auto& mmsBeamPipe */ mmsField.NewDaughter<MMSBeamPipe>(fCheckOverlap);
    /* auto& mmsMagnet */ mmsField.NewDaughter<MMSMagnet>(fCheckOverlap);
    /* auto& ttc */ mmsField.NewDaughter<TTC>(fCheckOverlap);

    /* auto& solenoidBeamPipeS1 */ solenoidFieldS1.NewDaughter<SolenoidBeamPipeS1>(fCheckOverlap);
    /* auto& solenoidS1 */ solenoidFieldS1.NewDaughter<SolenoidS1>(fCheckOverlap);
    /* auto& solenoidShieldS1 */ solenoidFieldS1.NewDaughter<SolenoidShieldS1>(fCheckOverlap);

    /* auto& filter */ solenoidFieldS2.NewDaughter<Filter>(fCheckOverlap);
    /* auto& solenoidBeamPipeS2 */ solenoidFieldS2.NewDaughter<SolenoidBeamPipeS2>(fCheckOverlap);
    /* auto& solenoidS2 */ solenoidFieldS2.NewDaughter<SolenoidS2>(fCheckOverlap);
    /* auto& solenoidShieldS2 */ solenoidFieldS2.NewDaughter<SolenoidShieldS2>(fCheckOverlap);

    /* auto& solenoidBeamPipeS3 */ solenoidFieldS3.NewDaughter<SolenoidBeamPipeS3>(fCheckOverlap);
    /* auto& solenoidS3 */ solenoidFieldS3.NewDaughter<SolenoidS3>(fCheckOverlap);
    /* auto& solenoidShieldS3 */ solenoidFieldS3.NewDaughter<SolenoidShieldS3>(fCheckOverlap);

    /* auto& solenoidT1 */ solenoidFieldT1.NewDaughter<SolenoidT1>(fCheckOverlap);
    /* auto& solenoidBeamPipeT1 */ solenoidFieldT1.NewDaughter<SolenoidBeamPipeT1>(fCheckOverlap);
    /* auto& solenoidShieldT1 */ solenoidFieldT1.NewDaughter<SolenoidShieldT1>(fCheckOverlap);

    /* auto& solenoidT2 */ solenoidFieldT2.NewDaughter<SolenoidT2>(fCheckOverlap);
    /* auto& solenoidBeamPipeT2 */ solenoidFieldT2.NewDaughter<SolenoidBeamPipeT2>(fCheckOverlap);
    /* auto& solenoidShieldT2 */ solenoidFieldT2.NewDaughter<SolenoidShieldT2>(fCheckOverlap);

    // 3

    auto& cdcGas{cdcBody.NewDaughter<CDCGas>(fCheckOverlap)};

    /* auto& accelerator */ acceleratorField.NewDaughter<Accelerator>(fCheckOverlap);
    /* auto& beamDegrader */ acceleratorField.NewDaughter<BeamDegrader>(fCheckOverlap);
    /* auto& beamMonitor */ acceleratorField.NewDaughter<BeamMonitor>(fCheckOverlap);
    /* auto& target */ acceleratorField.NewDaughter<Target>(fCheckOverlap);

    // 4

    auto& cdcSuperLayer{cdcGas.NewDaughter<CDCSuperLayer>(fCheckOverlap)};

    // 5

    auto& cdcSenseLayer{cdcSuperLayer.NewDaughter<CDCSenseLayer>(fCheckOverlap)};

    // 6

    /* auto& cdcCell */ cdcSenseLayer.NewDaughter<CDCCell>(fCheckOverlap);

    ////////////////////////////////////////////////////////////////
    // Register materials
    ////////////////////////////////////////////////////////////////
    {
        using namespace Mustard::LiteralUnit::Density;

        const auto nist = G4NistManager::Instance();

        const auto vacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3);
        acceleratorField.RegisterMaterial(vacuum);
        emcField.RegisterMaterial(vacuum);
        fWorld->RegisterMaterial(vacuum);
        mmsField.RegisterMaterial(vacuum);
        solenoidFieldS1.RegisterMaterial(vacuum);
        solenoidFieldS2.RegisterMaterial(vacuum);
        solenoidFieldS3.RegisterMaterial(vacuum);
        solenoidFieldT1.RegisterMaterial(vacuum);
        solenoidFieldT2.RegisterMaterial(vacuum);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    Mustard::Detector::Description::DescriptionIO::ExportInstantiated("test.yaml");

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    cdcSenseLayer.RemoveDaughter<CDCCell>(); // ROOT does not support twisted tube.
    fWorld->Export("test.gdml");

    auto geoManager = std::make_unique<TGeoManager>("MACEGeom", "MACE Geometry");
    geoManager->Import("test.gdml");

    /* // set transparency for jsroot display
    // see form https://github.com/root-project/jsroot/blob/master/docs/JSROOT.md#geometry-viewer

    geoManager->GetVolume(fWorld->LogicalVolume()->GetName())->SetInvisible();
    using Mustard::Detector::Definition::DefinitionBase;
    for (auto&& entity : std::initializer_list<std::reference_wrapper<const DefinitionBase>>{
             emcCrystal,
             emcMagnet,
             emcPMTAssemblies,
             emcShield,
             mmsMagnet,
             mmsShield,
             shieldingWall,
             solenoidT1,
             solenoidT2,
             solenoidS1,
             solenoidS2,
             solenoidS3}) {
        geoManager->GetVolume(entity.get().LogicalVolume()->GetName())->SetTransparency(60);
    } */

    geoManager->Export("test.root");

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    return EXIT_SUCCESS;
}
