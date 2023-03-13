#include "MACE/Geometry/DescriptionIO.hxx"
#include "MACE/Geometry/Entity/Fast/All.hxx"
#include "MACE/Env/BasicEnv.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4NistManager.hh"

#include "TGeoManager.h"

#include <functional>

int main(int argc, char* argv[]) {
    MACE::Env::BasicEnv env(argc, argv, {});

    ////////////////////////////////////////////////////////////////
    // Construct volumes
    ////////////////////////////////////////////////////////////////

    using namespace MACE::Geometry::Entity::Fast;

    constexpr auto fCheckOverlap = true;

    // 0

    const auto fWorld = std::make_unique_for_overwrite<World>();

    // 1

    auto& emCalField = fWorld->NewDaughter<EMCalField>(fCheckOverlap);
    auto& emCalShield = fWorld->NewDaughter<EMCalShield>(fCheckOverlap);
    auto& firstBendField = fWorld->NewDaughter<FirstBendField>(fCheckOverlap);
    auto& firstTransportField = fWorld->NewDaughter<FirstTransportField>(fCheckOverlap);
    auto& secondBendField = fWorld->NewDaughter<SecondBendField>(fCheckOverlap);
    auto& secondTransportField = fWorld->NewDaughter<SecondTransportField>(fCheckOverlap);
    auto& spectrometerField = fWorld->NewDaughter<SpectrometerField>(fCheckOverlap);
    auto& spectrometerShield = fWorld->NewDaughter<SpectrometerShield>(fCheckOverlap);
    auto& thirdTransportField = fWorld->NewDaughter<ThirdTransportField>(fCheckOverlap);

    // 2

    auto& emCal = emCalField.NewDaughter<EMCal>(fCheckOverlap);
    auto& mcp = emCalField.NewDaughter<MCP>(fCheckOverlap);

    auto& firstBendSolenoid = firstBendField.NewDaughter<FirstBendSolenoid>(fCheckOverlap);

    auto& firstTransportSolenoid = firstTransportField.NewDaughter<FirstTransportSolenoid>(fCheckOverlap);

    auto& secondBendSolenoid = secondBendField.NewDaughter<SecondBendSolenoid>(fCheckOverlap);

    auto& collimator = secondTransportField.NewDaughter<Collimator>(fCheckOverlap);
    auto& secondTransportSolenoid = secondTransportField.NewDaughter<SecondTransportSolenoid>(fCheckOverlap);
    auto& selectorField = secondTransportField.NewDaughter<SelectorField>(fCheckOverlap);

    auto& cdcBody = spectrometerField.NewDaughter<CDCBody>(fCheckOverlap);
    auto& linacField = spectrometerField.NewDaughter<LinacField>(fCheckOverlap);
    auto& spectrometerMagnet = spectrometerField.NewDaughter<SpectrometerMagnet>(fCheckOverlap);

    auto& thirdTransportSolenoid = thirdTransportField.NewDaughter<ThirdTransportSolenoid>(fCheckOverlap);

    // 3

    auto& cdcGas = cdcBody.NewDaughter<CDCGas>(fCheckOverlap);

    auto& beamDegrader = linacField.NewDaughter<BeamDegrader>(fCheckOverlap);
    auto& beamMonitor = linacField.NewDaughter<BeamMonitor>(fCheckOverlap);
    auto& target = linacField.NewDaughter<Target>(fCheckOverlap);

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

    const auto he = nist->FindOrBuildMaterial("G4_He");
    cdcCell.RegisterMaterial(he);
    cdcGas.RegisterMaterial(he);
    cdcSenseLayer.RegisterMaterial(he);
    cdcSuperLayer.RegisterMaterial(he);

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
    linacField.RegisterMaterial(vacuum);
    secondBendField.RegisterMaterial(vacuum);
    secondTransportField.RegisterMaterial(vacuum);
    selectorField.RegisterMaterial(vacuum);
    spectrometerField.RegisterMaterial(vacuum);
    thirdTransportField.RegisterMaterial(vacuum);
    fWorld->RegisterMaterial(vacuum);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    MACE::Geometry::DescriptionIO::ExportInstantiated("test.yaml");

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
    using MACE::Geometry::IEntity;
    for (auto&& entity : std::initializer_list<std::reference_wrapper<const IEntity>>{
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
