#include "G4NistManager.hh"

#include "detector/DetectorConstruction.hh"

using namespace MACE::SimG4;

DetectorConstruction::DetectorConstruction() :
    G4VUserDetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {
    delete fAcceleratorField;
    delete fCalorimeter;
    delete fCollimator;
    delete fFirstBendField;
    delete fFirstTransportField;
    delete fOrbitalDetector;
    delete fOrbitalDetectorShellField;
    delete fOrbitalDetectorShield;
    delete fSecondBendField;
    delete fSecondTransportField;
    delete fSelectorField;
    delete fSpectrometer;
    delete fSpectrometerField;
    delete fSpectrometerGas;
    delete fSpectrometerReadOutLayer;
    delete fSpectrometerShield;
    delete fTarget;
    delete fThirdTransportField;
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
    auto materialAl = nist->FindOrBuildMaterial("G4_Al");
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
    fSpectrometerField->Create(materialVacuum, fWorld);
    fAcceleratorField->Create(materialVacuum, fSpectrometerField);
    fFirstTransportField->Create(materialVacuum, fWorld);
    fFirstBendField->Create(materialVacuum, fWorld);
    fSecondTransportField->Create(materialVacuum, fWorld);
    fSelectorField->Create(materialVacuum, fSecondTransportField);
    fSecondBendField->Create(materialVacuum, fWorld);
    fThirdTransportField->Create(materialVacuum, fWorld);
    fOrbitalDetectorShellField->Create(materialVacuum, fWorld);
    // entities
    fTarget->Create(materialSilicaAerogel, fAcceleratorField);
    fSpectrometer->Create(materialAl, fSpectrometerField);
    fSpectrometerGas->Create(materialAr, fSpectrometer);
    fSpectrometerReadOutLayer->Create(materialAr, fSpectrometerGas);
    fCollimator->Create(materialCu, fSecondTransportField);
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
#include "detector/field/FirstBendField.hh"
#include "detector/field/ParallelField.hh"
#include "detector/field/SecondBendField.hh"
#include "detector/field/SelectorField.hh"
#include "detector/field/VerticalField.hh"

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
    auto parallelBField = new Field::ParallelField(defaultB);
    auto verticalBField = new Field::VerticalField(defaultB);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fSpectrometerField->GetLogicalVolume(), parallelBField, hMin, 6);

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
    >(fFirstTransportField->GetLogicalVolume(), parallelBField, hMin, 6);

    RegisterFields <
        Field::FirstBendField,
        G4TMagFieldEquation<Field::FirstBendField>,
        G4TDormandPrince45<G4TMagFieldEquation<Field::FirstBendField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<Field::FirstBendField>>>
    >(fFirstBendField->GetLogicalVolume(), new Field::FirstBendField(), hMin, 6);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fSecondTransportField->GetLogicalVolume(), verticalBField, hMin, 6);

    RegisterFields <
        Field::SelectorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(fSelectorField->GetLogicalVolume(), new Field::SelectorField(), hMin, 8);

    RegisterFields <
        Field::SecondBendField,
        G4TMagFieldEquation<Field::SecondBendField>,
        G4TDormandPrince45<G4TMagFieldEquation<Field::SecondBendField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<Field::SecondBendField>>>
    >(fSecondBendField->GetLogicalVolume(), new Field::SecondBendField(), hMin, 6);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fThirdTransportField->GetLogicalVolume(), parallelBField, hMin, 6);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fOrbitalDetectorShellField->GetLogicalVolume(), parallelBField, hMin, 6);
}