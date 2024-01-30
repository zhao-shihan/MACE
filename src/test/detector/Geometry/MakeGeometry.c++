#include "MACE/Detector/Description/DescriptionIO.h++"
#include "MACE/Detector/Geometry/Fast/AcceleratorField.h++"
#include "MACE/Detector/Geometry/Fast/BeamDegrader.h++"
#include "MACE/Detector/Geometry/Fast/BeamMonitor.h++"
#include "MACE/Detector/Geometry/Fast/CDCBody.h++"
#include "MACE/Detector/Geometry/Fast/CDCCell.h++"
#include "MACE/Detector/Geometry/Fast/CDCFieldWire.h++"
#include "MACE/Detector/Geometry/Fast/CDCGas.h++"
#include "MACE/Detector/Geometry/Fast/CDCSenseLayer.h++"
#include "MACE/Detector/Geometry/Fast/CDCSenseWire.h++"
#include "MACE/Detector/Geometry/Fast/CDCSuperLayer.h++"
#include "MACE/Detector/Geometry/Fast/EMCCrystal.h++"
#include "MACE/Detector/Geometry/Fast/EMCField.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTAssemblies.h++"
#include "MACE/Detector/Geometry/Fast/EMCPMTCoupler.h++"
#include "MACE/Detector/Geometry/Fast/EMCShield.h++"
#include "MACE/Detector/Geometry/Fast/Filter.h++"
#include "MACE/Detector/Geometry/Fast/MCP.h++"
#include "MACE/Detector/Geometry/Fast/ShieldingWall.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB1.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB1Field.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB2.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidB2Field.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS1.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS1Field.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS2.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS2Field.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS3.h++"
#include "MACE/Detector/Geometry/Fast/SolenoidS3Field.h++"
#include "MACE/Detector/Geometry/Fast/SpectrometerField.h++"
#include "MACE/Detector/Geometry/Fast/SpectrometerMagnet.h++"
#include "MACE/Detector/Geometry/Fast/SpectrometerShield.h++"
#include "MACE/Detector/Geometry/Fast/Target.h++"
#include "MACE/Detector/Geometry/Fast/World.h++"
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

    using namespace MACE::Detector::Geometry::Fast;

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
    auto& emcPMTCoupler = emcField.NewDaughter<EMCPMTCoupler>(fCheckOverlap);
    auto& emcPMTAssemblies = emcField.NewDaughter<EMCPMTAssemblies>(fCheckOverlap);

    auto& mcp = emcField.NewDaughter<MCP>(fCheckOverlap);

    auto& solenoidB1 = solenoidB1Field.NewDaughter<SolenoidB1>(fCheckOverlap);

    auto& solenoidS1 = solenoidS1Field.NewDaughter<SolenoidS1>(fCheckOverlap);

    auto& solenoidB2 = solenoidB2Field.NewDaughter<SolenoidB2>(fCheckOverlap);

    auto& filter = solenoidS2Field.NewDaughter<Filter>(fCheckOverlap);
    auto& solenoidS2 = solenoidS2Field.NewDaughter<SolenoidS2>(fCheckOverlap);

    auto& acceleratorField = spectrometerField.NewDaughter<AcceleratorField>(fCheckOverlap);
    auto& cdcBody = spectrometerField.NewDaughter<CDCBody>(fCheckOverlap);
    auto& spectrometerMagnet = spectrometerField.NewDaughter<SpectrometerMagnet>(fCheckOverlap);

    auto& solenoidS3 = solenoidS3Field.NewDaughter<SolenoidS3>(fCheckOverlap);

    // 3

    auto& cdcGas = cdcBody.NewDaughter<CDCGas>(fCheckOverlap);

    auto& beamDegrader = acceleratorField.NewDaughter<BeamDegrader>(fCheckOverlap);
    auto& beamMonitor = acceleratorField.NewDaughter<BeamMonitor>(fCheckOverlap);
    auto& target = acceleratorField.NewDaughter<Target>(fCheckOverlap);

    // 4

    auto& cdcSuperLayer = cdcGas.NewDaughter<CDCSuperLayer>(fCheckOverlap);

    // 5

    auto& cdcSenseLayer = cdcSuperLayer.NewDaughter<CDCSenseLayer>(fCheckOverlap);

    // 6

    auto& cdcFieldWire = cdcSenseLayer.NewDaughter<CDCFieldWire>(fCheckOverlap);
    auto& cdcCell = cdcSenseLayer.NewDaughter<CDCCell>(fCheckOverlap);

    // 7

    auto& cdcSenseWire = cdcCell.NewDaughter<CDCSenseWire>(fCheckOverlap);

    ////////////////////////////////////////////////////////////////
    // Register materials
    ////////////////////////////////////////////////////////////////
    {
        using namespace MACE::LiteralUnit::Density;

        const auto nist = G4NistManager::Instance();

        const auto aluminium = nist->FindOrBuildMaterial("G4_Al");
        beamDegrader.RegisterMaterial(aluminium);
        cdcFieldWire.RegisterMaterial(aluminium);

        const auto cdcHeBasedGas = [&nist] {
            constexpr auto heFraction = 0.85;
            constexpr auto butaneFraction = 1 - heFraction;
            const auto he = nist->FindOrBuildMaterial("G4_He");
            const auto butane = nist->FindOrBuildMaterial("G4_BUTANE");
            const auto gas = new G4Material("CDCGas",
                                            heFraction * he->GetDensity() +
                                                butaneFraction * butane->GetDensity(),
                                            2,
                                            kStateGas);
            gas->AddMaterial(he, heFraction);
            gas->AddMaterial(butane, butaneFraction);
            return gas;
        }();
        cdcCell.RegisterMaterial(cdcHeBasedGas);
        cdcGas.RegisterMaterial(cdcHeBasedGas);
        cdcSenseLayer.RegisterMaterial(cdcHeBasedGas);
        cdcSuperLayer.RegisterMaterial(cdcHeBasedGas);

        const auto cdcShell = nist->BuildMaterialWithNewDensity("CarbonFiber", "G4_C", 1.7_g_cm3);
        cdcBody.RegisterMaterial(cdcShell);

        const auto copper = nist->FindOrBuildMaterial("G4_Cu");
        solenoidB1.RegisterMaterial(copper);
        solenoidS1.RegisterMaterial(copper);
        solenoidB2.RegisterMaterial(copper);
        solenoidS2.RegisterMaterial(copper);
        solenoidS3.RegisterMaterial(copper);
        filter.RegisterMaterial(copper);

        // const auto csI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
        // emc.RegisterMaterial(csI);

        const auto iron = nist->FindOrBuildMaterial("G4_Fe");
        spectrometerMagnet.RegisterMaterial(iron);

        const auto lead = nist->FindOrBuildMaterial("G4_Pb");
        emcShield.RegisterMaterial(lead);
        spectrometerShield.RegisterMaterial(lead);

        const auto mcpMaterial = nist->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4_g_cm3);
        mcp.RegisterMaterial(mcpMaterial);

        const auto plasticScitillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
        beamMonitor.RegisterMaterial(plasticScitillator);

        const auto silicaAerogel = nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30_mg_cm3);
        target.RegisterMaterial(silicaAerogel);

        const auto tungsten = nist->FindOrBuildMaterial("G4_W");
        cdcSenseWire.RegisterMaterial(tungsten);

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
    using MACE::Detector::Geometry::GeometryBase;
    for (auto&& entity : std::initializer_list<std::reference_wrapper<const GeometryBase>>{
             emcShield,
             emcCrystal,
             emcPMTCoupler,
             emcPMTAssemblies,
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
