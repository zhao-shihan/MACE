#include "G4NistManager.hh"

#include "detector/DetectorConstruction.hh"
#include "detector/geometry/AcceleratorField.hh"
#include "detector/geometry/Calorimeter.hh"
#include "detector/geometry/Collimator.hh"
#include "detector/geometry/OrbitalDetector.hh"
#include "detector/geometry/OrbitalDetectorShellField.hh"
#include "detector/geometry/ParallelTransportField.hh"
#include "detector/geometry/SelectField.hh"
#include "detector/geometry/Spectrometer.hh"
#include "detector/geometry/SpectrometerField.hh"
#include "detector/geometry/Target.hh"
#include "detector/geometry/TurnField.hh"
#include "detector/geometry/VerticalTransportField.hh"
#include "detector/geometry/World.hh"

MACE::DetectorConstruction::DetectorConstruction() :
    G4VUserDetectorConstruction(),
    fAcceleratorField(new MACE::Geometry::AcceleratorField()),
    fCalorimeter(new MACE::Geometry::Calorimeter()),
    fCollimator(new MACE::Geometry::Collimator()),
    fOrbitalDetector(new MACE::Geometry::OrbitalDetector),
    fOrbitalDetectorShellField(new MACE::Geometry::OrbitalDetectorShellField()),
    fParallelTransportField(new MACE::Geometry::ParallelTransportField()),
    fSelectField(new MACE::Geometry::SelectField()),
    fSpectormeter(new MACE::Geometry::Spectrometer()),
    fSpectormeterField(new MACE::Geometry::SpectrometerField()),
    fTarget(new MACE::Geometry::Target()),
    fTurnField(new MACE::Geometry::TurnField()),
    fVerticalTransportField(new MACE::Geometry::VerticalTransportField()),
    fWorld(new MACE::Geometry::World) {}

MACE::DetectorConstruction::~DetectorConstruction() {
    delete fAcceleratorField;
    delete fCalorimeter;
    delete fCollimator;
    delete fOrbitalDetector;
    delete fOrbitalDetectorShellField;
    delete fParallelTransportField;
    delete fSelectField;
    delete fSpectormeter;
    delete fSpectormeterField;
    delete fTarget;
    delete fTurnField;
    delete fVerticalTransportField;
    delete fWorld;
}

G4VPhysicalVolume* MACE::DetectorConstruction::Construct() {
    //
    // materials
    //
    auto nist = G4NistManager::Instance();
    auto materialVacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1.16e-10 * g / m3);
    // auto materialPlexiGlass = nist->FindOrBuildMaterial("G4_PLEXIGLASS");
    // auto materialMylar = nist->FindOrBuildMaterial("G4_MYLAR");
    auto materialSilicaAerogel = nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30 * mg / cm3);
    auto materialMWPC = new G4Material("MWPC", 0.5 * g / cm3, 2);
    materialMWPC->AddElement(nist->FindOrBuildElement("Ar"), 0.8);
    materialMWPC->AddElement(nist->FindOrBuildElement("Al"), 0.2);
    // auto materialAl = nist->FindOrBuildMaterial("G4_Al");
    auto materialCu = nist->FindOrBuildMaterial("G4_Cu");
    // auto materialGraphite = nist->FindOrBuildMaterial("G4_GRAPHITE");
    auto materialMCP = nist->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4 * g / cm3);
    auto materialCsI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    // auto materialIron = nist->FindOrBuildMaterial("G4_Fe");
    //
    // make geometry
    //
    // world
    fWorld->Make(materialVacuum, nullptr);
    // fields
    fSpectormeterField->Make(materialVacuum, fWorld->GetPhysicalVolume());
    fAcceleratorField->Make(materialVacuum, fSpectormeterField->GetPhysicalVolume());
    fParallelTransportField->Make(materialVacuum, fWorld->GetPhysicalVolume());
    fSelectField->Make(materialVacuum, fParallelTransportField->GetPhysicalVolume());
    fTurnField->Make(materialVacuum, fWorld->GetPhysicalVolume());
    fVerticalTransportField->Make(materialVacuum, fWorld->GetPhysicalVolume());
    fOrbitalDetectorShellField->Make(materialVacuum, fWorld->GetPhysicalVolume());
    // entities
    fTarget->Make(materialSilicaAerogel, fAcceleratorField->GetPhysicalVolume());
    fSpectormeter->Make(materialMWPC, fSpectormeterField->GetPhysicalVolume());
    fCollimator->Make(materialCu, fVerticalTransportField->GetPhysicalVolume());
    fOrbitalDetector->Make(materialMCP, fOrbitalDetectorShellField->GetPhysicalVolume());
    fCalorimeter->Make(materialCsI, fOrbitalDetectorShellField->GetPhysicalVolume());
    return fWorld->GetPhysicalVolume();
}