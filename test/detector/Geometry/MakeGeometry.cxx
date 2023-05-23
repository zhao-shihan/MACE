#include "MACE/Detector/Description/DescriptionIO.hxx"
#include "MACE/Detector/Geometry/Fast/AcceleratorField.hxx"
#include "MACE/Detector/Geometry/Fast/BeamDegrader.hxx"
#include "MACE/Detector/Geometry/Fast/BeamMonitor.hxx"
#include "MACE/Detector/Geometry/Fast/CDCBody.hxx"
#include "MACE/Detector/Geometry/Fast/CDCCell.hxx"
#include "MACE/Detector/Geometry/Fast/CDCFieldWire.hxx"
#include "MACE/Detector/Geometry/Fast/CDCGas.hxx"
#include "MACE/Detector/Geometry/Fast/CDCSenseLayer.hxx"
#include "MACE/Detector/Geometry/Fast/CDCSenseWire.hxx"
#include "MACE/Detector/Geometry/Fast/CDCSuperLayer.hxx"
#include "MACE/Detector/Geometry/Fast/Collimator.hxx"
#include "MACE/Detector/Geometry/Fast/EMCal.hxx"
#include "MACE/Detector/Geometry/Fast/EMCalField.hxx"
#include "MACE/Detector/Geometry/Fast/EMCalShield.hxx"
#include "MACE/Detector/Geometry/Fast/MCP.hxx"
#include "MACE/Detector/Geometry/Fast/SelectorField.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidB1.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidB1Field.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidB2.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidB2Field.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidS1.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidS1Field.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidS2.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidS2Field.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidS3.hxx"
#include "MACE/Detector/Geometry/Fast/SolenoidS3Field.hxx"
#include "MACE/Detector/Geometry/Fast/SpectrometerField.hxx"
#include "MACE/Detector/Geometry/Fast/SpectrometerMagnet.hxx"
#include "MACE/Detector/Geometry/Fast/SpectrometerShield.hxx"
#include "MACE/Detector/Geometry/Fast/Target.hxx"
#include "MACE/Detector/Geometry/Fast/World.hxx"
#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Env/CLI/BasicCLI.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4NistManager.hh"

#include "TGeoManager.h"

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

    auto& emCalField = fWorld->NewDaughter<EMCalField>(fCheckOverlap);
    auto& emCalShield = fWorld->NewDaughter<EMCalShield>(fCheckOverlap);
    auto& firstBendField = fWorld->NewDaughter<SolenoidB1Field>(fCheckOverlap);
    auto& firstTransportField = fWorld->NewDaughter<SolenoidS1Field>(fCheckOverlap);
    auto& secondBendField = fWorld->NewDaughter<SolenoidB2Field>(fCheckOverlap);
    auto& secondTransportField = fWorld->NewDaughter<SolenoidS2Field>(fCheckOverlap);
    auto& spectrometerField = fWorld->NewDaughter<SpectrometerField>(fCheckOverlap);
    auto& spectrometerShield = fWorld->NewDaughter<SpectrometerShield>(fCheckOverlap);
    auto& thirdTransportField = fWorld->NewDaughter<SolenoidS3Field>(fCheckOverlap);

    // 2

    auto& emCal = emCalField.NewDaughter<EMCal>(fCheckOverlap);
    auto& mcp = emCalField.NewDaughter<MCP>(fCheckOverlap);

    auto& firstBendSolenoid = firstBendField.NewDaughter<SolenoidB1>(fCheckOverlap);

    auto& firstTransportSolenoid = firstTransportField.NewDaughter<SolenoidS1>(fCheckOverlap);

    auto& secondBendSolenoid = secondBendField.NewDaughter<SolenoidB2>(fCheckOverlap);

    auto& collimator = secondTransportField.NewDaughter<Collimator>(fCheckOverlap);
    auto& secondTransportSolenoid = secondTransportField.NewDaughter<SolenoidS2>(fCheckOverlap);
    auto& selectorField = secondTransportField.NewDaughter<SelectorField>(fCheckOverlap);

    auto& cdcBody = spectrometerField.NewDaughter<CDCBody>(fCheckOverlap);
    auto& acceleratorField = spectrometerField.NewDaughter<AcceleratorField>(fCheckOverlap);
    auto& spectrometerMagnet = spectrometerField.NewDaughter<SpectrometerMagnet>(fCheckOverlap);

    auto& thirdTransportSolenoid = thirdTransportField.NewDaughter<SolenoidS3>(fCheckOverlap);

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
    collimator.RegisterMaterial(copper);
    firstBendSolenoid.RegisterMaterial(copper);
    firstTransportSolenoid.RegisterMaterial(copper);
    secondBendSolenoid.RegisterMaterial(copper);
    secondTransportSolenoid.RegisterMaterial(copper);
    thirdTransportSolenoid.RegisterMaterial(copper);

    const auto csI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    emCal.RegisterMaterial(csI);

    const auto iron = nist->FindOrBuildMaterial("G4_Fe");
    spectrometerMagnet.RegisterMaterial(iron);

    const auto lead = nist->FindOrBuildMaterial("G4_Pb");
    emCalShield.RegisterMaterial(lead);
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
    emCalField.RegisterMaterial(vacuum);
    firstBendField.RegisterMaterial(vacuum);
    firstTransportField.RegisterMaterial(vacuum);
    acceleratorField.RegisterMaterial(vacuum);
    secondBendField.RegisterMaterial(vacuum);
    secondTransportField.RegisterMaterial(vacuum);
    selectorField.RegisterMaterial(vacuum);
    spectrometerField.RegisterMaterial(vacuum);
    thirdTransportField.RegisterMaterial(vacuum);
    fWorld->RegisterMaterial(vacuum);

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
             emCalShield,
             emCal,
             spectrometerMagnet,
             spectrometerShield,
             firstBendSolenoid,
             firstTransportSolenoid,
             secondBendSolenoid,
             secondTransportSolenoid,
             thirdTransportSolenoid}) {
        geoManager->GetVolume(entity.get().LogicalVolume()->GetName())->SetTransparency(60);
    }

    geoManager->Export("test.root");

#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    return EXIT_SUCCESS;
}
