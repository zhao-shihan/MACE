#include "G4NistManager.hh"

#include "detector/DetectorConstruction.hh"
#include "detector/geometry/AcceleratorField.hh"
#include "detector/geometry/Calorimeter.hh"
#include "detector/geometry/Collimator.hh"
#include "detector/geometry/OrbitalDetector.hh"
#include "detector/geometry/OrbitalDetectorShellField.hh"
#include "detector/geometry/OrbitalDetectorShield.hh"
#include "detector/geometry/ParallelTransportField.hh"
#include "detector/geometry/SelectField.hh"
#include "detector/geometry/Spectrometer.hh"
#include "detector/geometry/SpectrometerField.hh"
#include "detector/geometry/SpectrometerShield.hh"
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
    fOrbitalDetectorShield(new MACE::Geometry::OrbitalDetectorShield()),
    fParallelTransportField(new MACE::Geometry::ParallelTransportField()),
    fSelectField(new MACE::Geometry::SelectField()),
    fSpectormeter(new MACE::Geometry::Spectrometer()),
    fSpectormeterField(new MACE::Geometry::SpectrometerField()),
    fSpectrometerShield(new MACE::Geometry::SpectrometerShield()),
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
    delete fOrbitalDetectorShield;
    delete fParallelTransportField;
    delete fSelectField;
    delete fSpectormeter;
    delete fSpectormeterField;
    delete fSpectrometerShield;
    delete fTarget;
    delete fTurnField;
    delete fVerticalTransportField;
    delete fWorld;
}

G4VPhysicalVolume* MACE::DetectorConstruction::Construct() {
    ConstructGeometry();
    ConstructField();
    return fWorld->GetPhysicalVolume();
}

void MACE::DetectorConstruction::ConstructGeometry() {
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
    auto materialLead = nist->FindOrBuildMaterial("G4_Pb");
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
    fSpectrometerShield->Make(materialLead, fWorld->GetPhysicalVolume());
    fOrbitalDetectorShield->Make(materialLead, fWorld->GetPhysicalVolume());
}

#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4UniformElectricField.hh"
#include "G4TMagFieldEquation.hh"
#include "G4EqMagElectricField.hh"
#include "G4TDormandPrince45.hh"
#include "G4DormandPrince745.hh"
#include "G4IntegrationDriver.hh"
#include "G4ChordFinder.hh"

#include "detector/field/AcceleratorField.hh"
#include "detector/field/SelectField.hh"
#include "detector/field/TurnField.hh"

template<class Field_t, class Equation_t, class Stepper_t, class Driver_t>
static void RegisterFields(G4LogicalVolume* logicalVolume, Field_t* field, G4double hMin, G4int nVal) {
    auto equation = new Equation_t(field);
    auto stepper = new Stepper_t(equation, nVal);
    auto driver = new Driver_t(hMin, stepper, nVal);
    auto chordFinder = new G4ChordFinder(driver);
    logicalVolume->SetFieldManager(new G4FieldManager(field, chordFinder), true);
}

void MACE::DetectorConstruction::ConstructField() {
    constexpr G4double B = 0.1 * tesla;
    auto parallelBField = new G4UniformMagField(G4ThreeVector(0, 0, B));
    auto verticalBField = new G4UniformMagField(G4ThreeVector(B, 0, 0));

    constexpr G4double hMin = 100. * um;

    RegisterFields<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fSpectormeterField->GetLogicalVolume(), parallelBField, hMin, 6);

    RegisterFields <
        MACE::Field::AcceleratorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(fAcceleratorField->GetLogicalVolume(), new MACE::Field::AcceleratorField(), hMin, 8);

    RegisterFields <
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fParallelTransportField->GetLogicalVolume(), parallelBField, hMin, 6);

    RegisterFields <
        MACE::Field::SelectField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(fSelectField->GetLogicalVolume(), new MACE::Field::SelectField(), hMin, 8);

    RegisterFields <
        MACE::Field::TurnField,
        G4TMagFieldEquation<MACE::Field::TurnField>,
        G4TDormandPrince45<G4TMagFieldEquation<MACE::Field::TurnField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<MACE::Field::TurnField>>>
    >(fTurnField->GetLogicalVolume(), new MACE::Field::TurnField(), hMin, 6);

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