#include "G4NistManager.hh"

#include "SimG4/Action/DetectorConstruction.hxx"

using namespace MACE::SimG4::Action;

DetectorConstruction::DetectorConstruction() :
    G4VUserDetectorConstruction() {}

DetectorConstruction::~DetectorConstruction() {
    delete fWorld;
}

G4VPhysicalVolume* DetectorConstruction::Construct() {
    ConstructVolumes();
    ConstructSD();
    ConstructField();
    return fWorld->GetVolume();
}

void DetectorConstruction::ConstructVolumes() {
    fCalorimeterField->AddDaughter(fCalorimeter);
    fCalorimeterField->AddDaughter(fOrbitalDetector);
    fSecondTransportField->AddDaughter(fCollimator);
    fSecondTransportField->AddDaughter(fSelectorField);
    fSpectrometerField->AddDaughter(fAcceleratorField);
    fSpectrometerField->AddDaughter(fSpectrometerBody);
    fAcceleratorField->AddDaughter(fTarget);
    fSpectrometerBody->AddDaughter(fSpectrometerReadoutLayer);
    fSpectrometerReadoutLayer->AddDaughter(fSpectrometerCells);
    fWorld->AddDaughter(fCalorimeterField);
    fWorld->AddDaughter(fFirstBendField);
    fWorld->AddDaughter(fFirstBendSolenoid);
    fWorld->AddDaughter(fFirstTransportField);
    fWorld->AddDaughter(fFirstTransportSolenoid);
    fWorld->AddDaughter(fOrbitalDetectorShield);
    fWorld->AddDaughter(fSecondBendField);
    fWorld->AddDaughter(fSecondBendSolenoid);
    fWorld->AddDaughter(fSecondTransportField);
    fWorld->AddDaughter(fSecondTransportSolenoid);
    fWorld->AddDaughter(fSpectrometerField);
    fWorld->AddDaughter(fSpectrometerShield);
    fWorld->AddDaughter(fThirdTransportField);
    fWorld->AddDaughter(fThirdTransportSolenoid);

    fWorld->ConstructSelfAndDescendants();

    /* Deprecated.

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
    // fWorld
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

    fWorld->WriteGDML();
    */
}

#include "G4SDManager.hh"

#include "SimG4/SD/Calorimeter.hxx"
#include "SimG4/SD/OrbitalDetector.hxx"
#include "SimG4/SD/Spectrometer.hxx"

void DetectorConstruction::ConstructSD() {
    auto SDManager = G4SDManager::GetSDMpointer();

    auto logicCalorimeter = fCalorimeter->GetVolume()->GetLogicalVolume();
    auto fCalorimeterName = logicCalorimeter->GetName();
    auto fCalorimeterSD = new SD::Calorimeter(fCalorimeterName, fCalorimeterName + "HC");
    SDManager->AddNewDetector(fCalorimeterSD);
    SetSensitiveDetector(logicCalorimeter, fCalorimeterSD);

    auto logicOrbitalDetector = fOrbitalDetector->GetVolume()->GetLogicalVolume();
    auto fOrbitalDetectorName = logicOrbitalDetector->GetName();
    auto fOrbitalDetectorSD = new SD::OrbitalDetector(fOrbitalDetectorName, fOrbitalDetectorName + "HC");
    SDManager->AddNewDetector(fOrbitalDetectorSD);
    SetSensitiveDetector(logicOrbitalDetector, fOrbitalDetectorSD);

    std::set<G4LogicalVolume*> logicSpectrometerCells;
    for (size_t i = 0; i < fSpectrometerCells->GetVolumeNum(); ++i) {
        logicSpectrometerCells.insert(fSpectrometerCells->GetVolume(i)->GetLogicalVolume());
    }
    auto fSpectrometerName = (*logicSpectrometerCells.begin())->GetName();
    auto fSpectrometerSD = new SD::Spectrometer(fSpectrometerName, fSpectrometerName + "HC");
    SDManager->AddNewDetector(fSpectrometerSD);
    for (auto&& logicSpectrometerCell : logicSpectrometerCells) {
        SetSensitiveDetector(logicSpectrometerCell, fSpectrometerSD);
    }
}

#include "G4FieldManager.hh"
#include "G4TMagFieldEquation.hh"
#include "G4EqMagElectricField.hh"
#include "G4TDormandPrince45.hh"
#include "G4DormandPrince745.hh"
#include "G4IntegrationDriver.hh"
#include "G4ChordFinder.hh"

#include "SimG4/Field/AcceleratorField.hxx"
#include "SimG4/Field/FirstBendField.hxx"
#include "SimG4/Field/ParallelField.hxx"
#include "SimG4/Field/SecondBendField.hxx"
#include "SimG4/Field/SelectorField.hxx"
#include "SimG4/Field/VerticalField.hxx"

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
    >(fSpectrometerField->GetVolume()->GetLogicalVolume(), parallelBField, hMin, 6);

    RegisterFields <
        Field::AcceleratorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(fAcceleratorField->GetVolume()->GetLogicalVolume(), new Field::AcceleratorField(), hMin, 8);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fFirstTransportField->GetVolume()->GetLogicalVolume(), parallelBField, hMin, 6);

    RegisterFields <
        Field::FirstBendField,
        G4TMagFieldEquation<Field::FirstBendField>,
        G4TDormandPrince45<G4TMagFieldEquation<Field::FirstBendField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<Field::FirstBendField>>>
    >(fFirstBendField->GetVolume()->GetLogicalVolume(), new Field::FirstBendField(), hMin, 6);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fSecondTransportField->GetVolume()->GetLogicalVolume(), verticalBField, hMin, 6);

    RegisterFields <
        Field::SelectorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(fSelectorField->GetVolume()->GetLogicalVolume(), new Field::SelectorField(), hMin, 8);

    RegisterFields <
        Field::SecondBendField,
        G4TMagFieldEquation<Field::SecondBendField>,
        G4TDormandPrince45<G4TMagFieldEquation<Field::SecondBendField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<Field::SecondBendField>>>
    >(fSecondBendField->GetVolume()->GetLogicalVolume(), new Field::SecondBendField(), hMin, 6);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fThirdTransportField->GetVolume()->GetLogicalVolume(), parallelBField, hMin, 6);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fCalorimeterField->GetVolume()->GetLogicalVolume(), parallelBField, hMin, 6);
}