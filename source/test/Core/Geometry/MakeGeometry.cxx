#include "MACE/Core/Geometry/DescriptionIO.hxx"
#include "MACE/Core/Geometry/Entity/Fast/All.hxx"
#include "MACE/Environment/BasicEnvironment.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "G4NistManager.hh"

#include "TGeoManager.h"

using namespace MACE::Core::Geometry::Entity::Fast;

int main(int argc, char** argv) {
    MACE::Environment::BasicEnvironment env(argc, argv, {});

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    // Construct entity objects
    auto fBeamDegrader = std::make_shared<BeamDegrader>();
    auto fBeamMonitor = std::make_shared<BeamMonitor>();
    auto fCDCBody = std::make_shared<CDCBody>();
    auto fCDCCell = std::make_shared<CDCCell>();
    auto fCDCFieldWire = std::make_shared<CDCFieldWire>();
    auto fCDCLayer = std::make_shared<CDCLayer>();
    auto fCDCSenseWire = std::make_shared<CDCSenseWire>();
    auto fCDCSensitiveVolume = std::make_shared<CDCSensitiveVolume>();
    auto fCollimator = std::make_shared<Collimator>();
    auto fEMCal = std::make_shared<EMCal>();
    auto fEMCalField = std::make_shared<EMCalField>();
    auto fEMCalShield = std::make_shared<EMCalShield>();
    auto fFirstBendField = std::make_shared<FirstBendField>();
    auto fFirstBendSolenoid = std::make_shared<FirstBendSolenoid>();
    auto fFirstTransportField = std::make_shared<FirstTransportField>();
    auto fFirstTransportSolenoid = std::make_shared<FirstTransportSolenoid>();
    auto fLinacField = std::make_shared<LinacField>();
    auto fMCP = std::make_shared<MCP>();
    auto fSecondBendField = std::make_shared<SecondBendField>();
    auto fSecondBendSolenoid = std::make_shared<SecondBendSolenoid>();
    auto fSecondTransportField = std::make_shared<SecondTransportField>();
    auto fSecondTransportSolenoid = std::make_shared<SecondTransportSolenoid>();
    auto fSelectorField = std::make_shared<SelectorField>();
    auto fSpectrometerField = std::make_shared<SpectrometerField>();
    auto fSpectrometerMagnet = std::make_shared<SpectrometerMagnet>();
    auto fSpectrometerShield = std::make_shared<SpectrometerShield>();
    auto fTarget = std::make_shared<Target>();
    auto fThirdTransportField = std::make_shared<ThirdTransportField>();
    auto fThirdTransportSolenoid = std::make_shared<ThirdTransportSolenoid>();
    auto fWorld = std::make_shared<World>();

    // Construct hierarchy
    fCDCBody->AddDaughter(fCDCLayer);
    fCDCCell->AddDaughter(fCDCFieldWire);
    fCDCCell->AddDaughter(fCDCSensitiveVolume);
    fCDCLayer->AddDaughter(fCDCCell);
    fCDCSensitiveVolume->AddDaughter(fCDCSenseWire);
    fEMCalField->AddDaughter(fEMCal);
    fEMCalField->AddDaughter(fMCP);
    fFirstBendField->AddDaughter(fFirstBendSolenoid);
    fFirstTransportField->AddDaughter(fFirstTransportSolenoid);
    fLinacField->AddDaughter(fBeamDegrader);
    fLinacField->AddDaughter(fBeamMonitor);
    fLinacField->AddDaughter(fTarget);
    fSecondBendField->AddDaughter(fSecondBendSolenoid);
    fSecondTransportField->AddDaughter(fCollimator);
    fSecondTransportField->AddDaughter(fSecondTransportSolenoid);
    fSecondTransportField->AddDaughter(fSelectorField);
    fSpectrometerField->AddDaughter(fCDCBody);
    fSpectrometerField->AddDaughter(fLinacField);
    fSpectrometerField->AddDaughter(fSpectrometerMagnet);
    fThirdTransportField->AddDaughter(fThirdTransportSolenoid);
    fWorld->AddDaughter(fEMCalField);
    fWorld->AddDaughter(fEMCalShield);
    fWorld->AddDaughter(fFirstBendField);
    fWorld->AddDaughter(fFirstTransportField);
    fWorld->AddDaughter(fSecondBendField);
    fWorld->AddDaughter(fSecondTransportField);
    fWorld->AddDaughter(fSpectrometerField);
    fWorld->AddDaughter(fSpectrometerShield);
    fWorld->AddDaughter(fThirdTransportField);

    // Construct volumes
    fWorld->ConstructSelfAndDescendants(true);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    using namespace MACE::Utility::LiteralUnit;

    auto nist = G4NistManager::Instance();

    auto aluminium = nist->FindOrBuildMaterial("G4_Al");
    fBeamDegrader->RegisterMaterial(aluminium);
    fCDCFieldWire->RegisterMaterial(aluminium);

    auto cdcGas = nist->FindOrBuildMaterial("G4_He");
    fCDCCell->RegisterMaterial(cdcGas);
    fCDCLayer->RegisterMaterial(cdcGas);
    fCDCSensitiveVolume->RegisterMaterial(cdcGas);

    auto cdcShell = nist->BuildMaterialWithNewDensity("CarbonFiber", "G4_C", 1.7_g_cm3);
    fCDCBody->RegisterMaterial(cdcShell);

    auto copper = nist->FindOrBuildMaterial("G4_Cu");
    fCollimator->RegisterMaterial(copper);
    fFirstBendSolenoid->RegisterMaterial(copper);
    fFirstTransportSolenoid->RegisterMaterial(copper);
    fSecondBendSolenoid->RegisterMaterial(copper);
    fSecondTransportSolenoid->RegisterMaterial(copper);
    fThirdTransportSolenoid->RegisterMaterial(copper);

    auto csI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    fEMCal->RegisterMaterial(csI);

    auto iron = nist->FindOrBuildMaterial("G4_Fe");
    fSpectrometerMagnet->RegisterMaterial(iron);

    auto lead = nist->FindOrBuildMaterial("G4_Pb");
    fEMCalShield->RegisterMaterial(lead);
    fSpectrometerShield->RegisterMaterial(lead);

    auto mcpMaterial = nist->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4_g_cm3);
    fMCP->RegisterMaterial(mcpMaterial);

    auto mylar = nist->FindOrBuildMaterial("G4_MYLAR");
    fBeamDegrader->RegisterMaterial(mylar);

    auto plasticScitillator = nist->FindOrBuildMaterial("G4_PLASTIC_SC_VINYLTOLUENE");
    fBeamMonitor->RegisterMaterial(plasticScitillator);

    auto silicaAerogel = nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30_mg_cm3);
    fTarget->RegisterMaterial(silicaAerogel);

    auto tungsten = nist->FindOrBuildMaterial("G4_W");
    fCDCSenseWire->RegisterMaterial(tungsten);

    auto vacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1e-12_g_cm3);
    fEMCalField->RegisterMaterial(vacuum);
    fFirstBendField->RegisterMaterial(vacuum);
    fFirstTransportField->RegisterMaterial(vacuum);
    fLinacField->RegisterMaterial(vacuum);
    fSecondBendField->RegisterMaterial(vacuum);
    fSecondTransportField->RegisterMaterial(vacuum);
    fSelectorField->RegisterMaterial(vacuum);
    fSpectrometerField->RegisterMaterial(vacuum);
    fThirdTransportField->RegisterMaterial(vacuum);
    fWorld->RegisterMaterial(vacuum);

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    MACE::Core::Geometry::DescriptionIO::ExportInstantiated("test.yaml");

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

#if MACE_WITH_G4GDML

    fWorld->Export("test.gdml");

    auto geoManager = std::make_unique<TGeoManager>("MACEGeom", "MACE Geometry");
    geoManager->Import("test.gdml");

    // set transparency for jsroot display
    // see form https://github.com/root-project/jsroot/blob/master/docs/JSROOT.md#geometry-viewer
    geoManager->GetVolume(fWorld->GetLogicalVolume()->GetName())->SetInvisible();
    std::vector<std::shared_ptr<MACE::Core::Geometry::IEntity>> volumesToSetTransparency{
        fEMCalShield,
        fEMCal,
        fSpectrometerMagnet,
        fSpectrometerShield,
        fFirstBendSolenoid,
        fFirstTransportSolenoid,
        fSecondBendSolenoid,
        fSecondTransportSolenoid,
        fThirdTransportSolenoid};
    for (auto&& volume : std::as_const(volumesToSetTransparency)) {
        geoManager->GetVolume(volume->GetLogicalVolume()->GetName())->SetTransparency(60);
    }

    geoManager->Export("test.root");

#endif

    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////////

    return EXIT_SUCCESS;
}
