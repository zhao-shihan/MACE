#include "G4NistManager.hh"

#include "detector/DetectorConstruction.hh"

using namespace MACE::SimG4;

#include "detector/geometry/AcceleratorField.hh"
#include "detector/geometry/Calorimeter.hh"
#include "detector/geometry/Collimator.hh"
#include "detector/geometry/OrbitalDetector.hh"
#include "detector/geometry/OrbitalDetectorShellField.hh"
#include "detector/geometry/OrbitalDetectorShield.hh"
#include "detector/geometry/ParallelTransportField.hh"
#include "detector/geometry/SelectorField.hh"
#include "detector/geometry/Spectrometer.hh"
#include "detector/geometry/SpectrometerField.hh"
#include "detector/geometry/SpectrometerReadOutLayer.hh"
#include "detector/geometry/SpectrometerShield.hh"
#include "detector/geometry/Target.hh"
#include "detector/geometry/CounterClockwiseGuideField.hh"
#include "detector/geometry/VerticalTransportField.hh"
#include "detector/geometry/World.hh"

DetectorConstruction::DetectorConstruction() :
    G4VUserDetectorConstruction(),
    fAcceleratorField(new Geometry::AcceleratorField()),
    fCalorimeter(new Geometry::Calorimeter()),
    fCollimator(new Geometry::Collimator()),
    fOrbitalDetector(new Geometry::OrbitalDetector),
    fOrbitalDetectorShellField(new Geometry::OrbitalDetectorShellField()),
    fOrbitalDetectorShield(new Geometry::OrbitalDetectorShield()),
    fParallelTransportField(new Geometry::ParallelTransportField()),
    fSelectorField(new Geometry::SelectorField()),
    fSpectormeter(new Geometry::Spectrometer()),
    fSpectormeterField(new Geometry::SpectrometerField()),
    fSpectrometerReadOutLayer(new Geometry::SpectrometerReadOutLayer()),
    fSpectrometerShield(new Geometry::SpectrometerShield()),
    fTarget(new Geometry::Target()),
    fCounterClockwiseGuideField(new Geometry::CounterClockwiseGuideField()),
    fVerticalTransportField(new Geometry::VerticalTransportField()),
    fWorld(new Geometry::World) {}

DetectorConstruction::~DetectorConstruction() {
    delete fAcceleratorField;
    delete fCalorimeter;
    delete fCollimator;
    delete fOrbitalDetector;
    delete fOrbitalDetectorShellField;
    delete fOrbitalDetectorShield;
    delete fParallelTransportField;
    delete fSelectorField;
    delete fSpectormeter;
    delete fSpectormeterField;
    delete fSpectrometerReadOutLayer;
    delete fSpectrometerShield;
    delete fTarget;
    delete fCounterClockwiseGuideField;
    delete fVerticalTransportField;
    delete fWorld;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    ConstructGeometry();
    ConstructSD();
    ConstructField();
    return fWorld->GetPhysicalVolume();
}

void DetectorConstruction::ConstructGeometry() {
    //
    // materials
    //
    auto nist = G4NistManager::Instance();
    auto materialVacuum = nist->BuildMaterialWithNewDensity("Vacuum", "G4_AIR", 1.16e-10 * g / m3);
    // auto materialPlexiGlass = nist->FindOrBuildMaterial("G4_PLEXIGLASS");
    // auto materialMylar = nist->FindOrBuildMaterial("G4_MYLAR");
    auto materialSilicaAerogel = nist->BuildMaterialWithNewDensity("SilicaAerogel", "G4_SILICON_DIOXIDE", 30 * mg / cm3);
    auto materialAr = nist->FindOrBuildMaterial("G4_Ar");
    // auto materialAl = nist->FindOrBuildMaterial("G4_Al");
    auto materialCu = nist->FindOrBuildMaterial("G4_Cu");
    // auto materialGraphite = nist->FindOrBuildMaterial("G4_GRAPHITE");
    auto materialMCP = nist->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4 * g / cm3);
    auto materialCsI = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    auto materialLead = nist->FindOrBuildMaterial("G4_Pb");
    //
    // create geometry
    //
    // world
    fWorld->Create(materialVacuum, nullptr);
    // fields
    fSpectormeterField->Create(materialVacuum, fWorld);
    fAcceleratorField->Create(materialVacuum, fSpectormeterField);
    fParallelTransportField->Create(materialVacuum, fWorld);
    fSelectorField->Create(materialVacuum, fParallelTransportField);
    fCounterClockwiseGuideField->Create(materialVacuum, fWorld);
    fVerticalTransportField->Create(materialVacuum, fWorld);
    fOrbitalDetectorShellField->Create(materialVacuum, fWorld);
    // entities
    fTarget->Create(materialSilicaAerogel, fAcceleratorField);
    fSpectormeter->Create(materialAr, fSpectormeterField);
    fSpectrometerReadOutLayer->Create(materialAr, fSpectormeter);
    fCollimator->Create(materialCu, fVerticalTransportField);
    fOrbitalDetector->Create(materialMCP, fOrbitalDetectorShellField);
    fCalorimeter->Create(materialCsI, fOrbitalDetectorShellField);
    fSpectrometerShield->Create(materialLead, fWorld);
    fOrbitalDetectorShield->Create(materialLead, fWorld);
}

#include "G4SDManager.hh"

#include "detector/SD/Calorimeter.hh"
#include "detector/SD/OrbitalDetector.hh"
#include "detector/SD/Spectrometer.hh"

void DetectorConstruction::ConstructSD() {
    auto SDManager = G4SDManager::GetSDMpointer();

    auto calorimeterName = fCalorimeter->GetLogicalVolume()->GetName();
    auto calorimeterSD = new SD::Calorimeter(calorimeterName, calorimeterName + "HC");
    SDManager->AddNewDetector(calorimeterSD);
    SetSensitiveDetector(fCalorimeter->GetLogicalVolume(), calorimeterSD);

    auto orbitalDetectorName = fOrbitalDetector->GetLogicalVolume()->GetName();
    auto orbitalDetectorSD = new SD::OrbitalDetector(orbitalDetectorName, orbitalDetectorName + "HC");
    SDManager->AddNewDetector(orbitalDetectorSD);
    SetSensitiveDetector(fOrbitalDetector->GetLogicalVolume(), orbitalDetectorSD);

    auto spectrometerName = fSpectrometerReadOutLayer->GetLogicalVolume()->GetName();
    auto spectrometerSD = new SD::Spectrometer(spectrometerName, spectrometerName + "HC");
    SDManager->AddNewDetector(spectrometerSD);
    for (size_t i = 0; i < fSpectrometerReadOutLayer->GetVolumeSetCount(); ++i) {
        SetSensitiveDetector(fSpectrometerReadOutLayer->GetLogicalVolume(i), spectrometerSD);
    }
}

#include "G4FieldManager.hh"
#include "G4TMagFieldEquation.hh"
#include "G4EqMagElectricField.hh"
#include "G4TDormandPrince45.hh"
#include "G4DormandPrince745.hh"
#include "G4IntegrationDriver.hh"
#include "G4ChordFinder.hh"

#include "detector/field/AcceleratorField.hh"
#include "detector/field/ParallelTransportField.hh"
#include "detector/field/SelectorField.hh"
#include "detector/field/CounterClockwiseGuideField.hh"
#include "detector/field/VerticalTransportField.hh"

template<class Field_t, class Equation_t, class Stepper_t, class Driver_t>
static void RegisterFields(G4LogicalVolume* logicalVolume, Field_t* field, G4double hMin, G4int nVal) {
    auto equation = new Equation_t(field);
    auto stepper = new Stepper_t(equation, nVal);
    auto driver = new Driver_t(hMin, stepper, nVal);
    auto chordFinder = new G4ChordFinder(driver);
    logicalVolume->SetFieldManager(new G4FieldManager(field, chordFinder), true);
}

void DetectorConstruction::ConstructField() {
    constexpr G4double hMin = 100. * um;
    
    constexpr G4double defaultB = 0.1 * tesla;
    auto parallelBField = new Field::ParallelTransportField(defaultB);
    auto verticalBField = new Field::VerticalTransportField(defaultB);
    
    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fSpectormeterField->GetLogicalVolume(), parallelBField, hMin, 6);

    RegisterFields <
        Field::AcceleratorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(fAcceleratorField->GetLogicalVolume(), new Field::AcceleratorField(), hMin, 8);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fParallelTransportField->GetLogicalVolume(), parallelBField, hMin, 6);

    RegisterFields <
        Field::SelectorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(fSelectorField->GetLogicalVolume(), new Field::SelectorField(), hMin, 8);

    RegisterFields <
        Field::CounterClockwiseGuideField,
        G4TMagFieldEquation<Field::CounterClockwiseGuideField>,
        G4TDormandPrince45<G4TMagFieldEquation<Field::CounterClockwiseGuideField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<Field::CounterClockwiseGuideField>>>
    >(fCounterClockwiseGuideField->GetLogicalVolume(), new Field::CounterClockwiseGuideField(), hMin, 6);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fVerticalTransportField->GetLogicalVolume(), verticalBField, hMin, 6);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fOrbitalDetectorShellField->GetLogicalVolume(), verticalBField, hMin, 6);
}