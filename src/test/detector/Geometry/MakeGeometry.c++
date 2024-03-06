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
#include "MACE/Detector/Definition/ShieldingWall.h++"
#include "MACE/Detector/Definition/SolenoidB1.h++"
#include "MACE/Detector/Definition/SolenoidB1Field.h++"
#include "MACE/Detector/Definition/SolenoidB2.h++"
#include "MACE/Detector/Definition/SolenoidB2Field.h++"
#include "MACE/Detector/Definition/SolenoidS1.h++"
#include "MACE/Detector/Definition/SolenoidS1Field.h++"
#include "MACE/Detector/Definition/SolenoidS2.h++"
#include "MACE/Detector/Definition/SolenoidS2Field.h++"
#include "MACE/Detector/Definition/SolenoidS3.h++"
#include "MACE/Detector/Definition/SolenoidS3Field.h++"
#include "MACE/Detector/Definition/SpectrometerField.h++"
#include "MACE/Detector/Definition/SpectrometerMagnet.h++"
#include "MACE/Detector/Definition/SpectrometerShield.h++"
#include "MACE/Detector/Definition/Target.h++"
#include "MACE/Detector/Definition/World.h++"
#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Env/BasicEnv.h++"
#include "MACE/Env/CLI/BasicCLI.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "TGeoManager.h"

#include "G4NistManager.hh"

#include <functional>

int main(int argc, char* argv[]) {
    MACE::Env::CLI::BasicCLI cli;
    MACE::Env::BasicEnv env(argc, argv, cli);

    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    using namespace MACE::Detector::Definition;

    constexpr auto fCheckOverlap = true;

    // 0

    const auto fWorld = std::make_unique_for_overwrite<World>();

    // 1

    auto& emcField = fWorld->NewDaughter<EMCField>(fCheckOverlap);
    auto& emcShield = fWorld->NewDaughter<EMCShield>(fCheckOverlap);
    auto& solenoidB1Field = fWorld->NewDaughter<SolenoidB1Field>(fCheckOverlap);
    auto& solenoidB2Field = fWorld->NewDaughter<SolenoidB2Field>(fCheckOverlap);
    auto& solenoidS1Field = fWorld->NewDaughter<SolenoidS1Field>(fCheckOverlap);
    auto& solenoidS2Field = fWorld->NewDaughter<SolenoidS2Field>(fCheckOverlap);
    auto& solenoidS3Field = fWorld->NewDaughter<SolenoidS3Field>(fCheckOverlap);
    auto& spectrometerField = fWorld->NewDaughter<SpectrometerField>(fCheckOverlap);
    auto& spectrometerShield = fWorld->NewDaughter<SpectrometerShield>(fCheckOverlap);
    auto& shieldingWall = fWorld->NewDaughter<ShieldingWall>(fCheckOverlap);

    // 2

    auto& emcCrystal = emcField.NewDaughter<EMCCrystal>(fCheckOverlap);
    auto& emcPMTAssemblies = emcField.NewDaughter<EMCPMTAssemblies>(fCheckOverlap);
    auto& emcMagnet = emcField.NewDaughter<EMCMagnet>(fCheckOverlap);

    /* auto& mcp = */ emcField.NewDaughter<MCP>(fCheckOverlap);

    auto& solenoidB1 = solenoidB1Field.NewDaughter<SolenoidB1>(fCheckOverlap);

    auto& solenoidS1 = solenoidS1Field.NewDaughter<SolenoidS1>(fCheckOverlap);

    auto& solenoidB2 = solenoidB2Field.NewDaughter<SolenoidB2>(fCheckOverlap);

    /* auto& filter = */ solenoidS2Field.NewDaughter<Filter>(fCheckOverlap);
    auto& solenoidS2 = solenoidS2Field.NewDaughter<SolenoidS2>(fCheckOverlap);

    auto& acceleratorField = spectrometerField.NewDaughter<AcceleratorField>(fCheckOverlap);
    auto& cdcBody = spectrometerField.NewDaughter<CDCBody>(fCheckOverlap);
    auto& spectrometerMagnet = spectrometerField.NewDaughter<SpectrometerMagnet>(fCheckOverlap);

    auto& solenoidS3 = solenoidS3Field.NewDaughter<SolenoidS3>(fCheckOverlap);

    // 3

    auto& cdcGas = cdcBody.NewDaughter<CDCGas>(fCheckOverlap);

    /* auto& beamDegrader = */ acceleratorField.NewDaughter<BeamDegrader>(fCheckOverlap);
    /* auto& beamMonitor = */ acceleratorField.NewDaughter<BeamMonitor>(fCheckOverlap);
    /* auto& target = */ acceleratorField.NewDaughter<Target>(fCheckOverlap);

    // 4

    auto& cdcSuperLayer = cdcGas.NewDaughter<CDCSuperLayer>(fCheckOverlap);

    // 5

    auto& cdcSenseLayer = cdcSuperLayer.NewDaughter<CDCSenseLayer>(fCheckOverlap);

    // 6

    /* auto& cdcCell = */ cdcSenseLayer.NewDaughter<CDCCell>(fCheckOverlap);

    ////////////////////////////////////////////////////////////////
    // Register materials
    ////////////////////////////////////////////////////////////////
    {
        using namespace MACE::LiteralUnit::Density;

        const auto nist = G4NistManager::Instance();

        const auto vacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3);
        emcField.RegisterMaterial(vacuum);
        solenoidB1Field.RegisterMaterial(vacuum);
        solenoidS1Field.RegisterMaterial(vacuum);
        acceleratorField.RegisterMaterial(vacuum);
        solenoidB2Field.RegisterMaterial(vacuum);
        solenoidS2Field.RegisterMaterial(vacuum);
        spectrometerField.RegisterMaterial(vacuum);
        solenoidS3Field.RegisterMaterial(vacuum);
        fWorld->RegisterMaterial(vacuum);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    MACE::Detector::Description::DescriptionIO::ExportInstantiated("test.yaml");

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

#if MACE_USE_G4GDML

    cdcSenseLayer.RemoveDaughter<CDCCell>(); // ROOT does not support twisted tube.
    fWorld->Export("test.gdml");

    auto geoManager = std::make_unique<TGeoManager>("MACEGeom", "MACE Geometry");
    geoManager->Import("test.gdml");

    // set transparency for jsroot display
    // see form https://github.com/root-project/jsroot/blob/master/docs/JSROOT.md#geometry-viewer

    geoManager->GetVolume(fWorld->LogicalVolume()->GetName())->SetInvisible();
    using MACE::Detector::Definition::DefinitionBase;
    for (auto&& entity : std::initializer_list<std::reference_wrapper<const DefinitionBase>>{
             emcShield,
             emcCrystal,
             emcPMTAssemblies,
             emcMagnet,
             spectrometerMagnet,
             spectrometerShield,
             shieldingWall,
             solenoidB1,
             solenoidB2,
             solenoidS1,
             solenoidS2,
             solenoidS3}) {
        geoManager->GetVolume(entity.get().LogicalVolume()->GetName())->SetTransparency(60);
    }

    geoManager->Export("test.root");

#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    return EXIT_SUCCESS;
}
