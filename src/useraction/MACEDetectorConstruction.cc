// MACEDetectorConstruction
//
// Author:	Yuzhe Mao 02.2020
//
// Review and update: Shihan Zhao 05.2021
// 
// Simulation of MACE Muonium-AntiMuonium Conversion Expriment Detector
// Missing collimator and beam counter.

#include "G4SystemOfUnits.hh"
#include "G4SubtractionSolid.hh"
#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4UserLimits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4Material.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"
#include "G4TMagFieldEquation.hh"
#include "G4EqMagElectricField.hh"
#include "G4TDormandPrince45.hh"
#include "G4DormandPrince745.hh"
#include "G4IntegrationDriver.hh"
#include "G4ChordFinder.hh"

#include "useraction/MACEDetectorConstruction.hh"
#include "SD/MACEMWPCSD.hh"
#include "SD/MACEMCPSD.hh"
#include "SD/MACECsISD.hh"
#include "fields/MACEAcceleratorField.hh"
#include "fields/MACESeparatorField.hh"
#include "fields/MACETransportField2.hh"

MACEDetectorConstruction::MACEDetectorConstruction() :
    G4VUserDetectorConstruction(),
    fLogicalMWPC{ nullptr },
    fLogicalMCP(nullptr),
    fLogicalCsI(nullptr),

    fLogicalTransportField1(nullptr),
    fLogicalAcceleratorField(nullptr),
    fLogicalMagneticSpectrometerField(nullptr),
    fLogicalSeparatorField(nullptr),
    fLogicalTransportField2(nullptr),
    fLogicalTransportField3(nullptr),
    fLogicalCsIShellField(nullptr),

    fTransportField2Z(0.),

    fPhysicalSiO2Target(nullptr),
    fPhysicalMagneticSpectrometerShield{ nullptr },
    fPhysicalCsIShield{ nullptr } {}

MACEDetectorConstruction::~MACEDetectorConstruction() {}

G4VPhysicalVolume* MACEDetectorConstruction::Construct() {

    ////////////////////////////////////////////////////////////////////////////
    //                             Material                                   //
    ////////////////////////////////////////////////////////////////////////////

    G4NistManager* nistManager = G4NistManager::Instance();
    auto materialVacuo = nistManager->BuildMaterialWithNewDensity("Vacuo", "G4_AIR", 1e-24 * g / cm3);
    auto materialPlexiGlass = nistManager->FindOrBuildMaterial("G4_PLEXIGLASS");
    auto materialMylar = nistManager->FindOrBuildMaterial("G4_MYLAR");
    auto materialSiO2 = nistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    auto materialMWPC = new G4Material("MWPC", 0.5 * g / cm3, 2);
    auto materialAl = nistManager->FindOrBuildMaterial("G4_Al");
    auto materialGraphite = nistManager->FindOrBuildMaterial("G4_GRAPHITE");
    auto materialCu = nistManager->FindOrBuildMaterial("G4_Cu");
    auto materialCsI = nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    auto materialMCP = nistManager->BuildMaterialWithNewDensity("MCP", "G4_GLASS_PLATE", 1.4 * g / cm3);
    auto materialIron = nistManager->FindOrBuildMaterial("G4_Fe");

    materialMWPC->AddElement(nistManager->FindOrBuildElement("Ar"), 0.8);
    materialMWPC->AddElement(nistManager->FindOrBuildElement("Al"), 0.2);

    ////////////////////////////////////////////////////////////////////////////
    //                             Geometry                                   //
    ////////////////////////////////////////////////////////////////////////////

    constexpr G4bool checkSurfaceOverlaps = false;

    //--------------------------------------------------------------------------
    // Solid world.
    //--------------------------------------------------------------------------

    auto solidWorld = new G4Box(
        "World",
        3.0 * m,
        1.0 * m,
        3.0 * m
    );

    //--------------------------------------------------------------------------
    // Solid fields.
    //--------------------------------------------------------------------------

    constexpr G4double fieldOverlaps = 1. * nm;
    constexpr G4double solidTransportField1Dz = 0.5 * (47. - (8. * 0.866025403784439 + 1.)) * cm;
    constexpr G4double solidAcceleratorFieldDz = 0.5 * (40. + 8. * 0.866025403784439 + 1.) * cm;
    constexpr G4double solidMagneticSpectrometerFieldDz = 47. * cm;
    constexpr G4double solidSeparatorFieldDz = 42.5 * cm;
    constexpr G4double solidTransportField2Dz = 35. * cm;
    constexpr G4double solidTransportField3Dz = 50. * cm;
    constexpr G4double solidCsIShellFieldDz = 40. * cm;

    auto solidTransportField1 = new G4Tubs(
        "TransportField1",
        0. * cm,
        8.1 * cm + fieldOverlaps,
        solidTransportField1Dz + fieldOverlaps,
        0. * deg,
        360. * deg
    );
    auto solidAcceleratorField = new G4Tubs(
        "AcceleratorField",
        0. * cm,
        8.1 * cm + fieldOverlaps,
        solidAcceleratorFieldDz + fieldOverlaps,
        0. * deg,
        360. * deg
    );
    auto solidMagneticSpectrometerField = new G4Tubs(
        "MagneticSpectrometerField",
        8.1 * cm - fieldOverlaps,
        37.0 * cm,
        solidMagneticSpectrometerFieldDz + fieldOverlaps,
        0. * deg,
        360. * deg
    );
    auto solidSeparatorField = new G4Tubs(
        "SeparatorField",
        0. * cm,
        8.1 * cm + fieldOverlaps,
        solidSeparatorFieldDz + fieldOverlaps,
        0. * deg,
        360. * deg
    );
    auto solidTransportField2 = new G4Box(
        "TransportField2",
        solidTransportField2Dz + fieldOverlaps,
        12. * cm,
        solidTransportField2Dz + fieldOverlaps
    );
    auto solidTransportField3 = new G4Tubs(
        "TransportField3",
        0. * cm,
        10.5 * cm,
        solidTransportField3Dz + fieldOverlaps,
        0. * deg,
        360. * deg
    );
    auto solidCsIShellField = new G4Tubs(
        "CsIShellField",
        0. * cm,
        23. * cm,
        solidCsIShellFieldDz + fieldOverlaps,
        0. * deg,
        360. * deg
    );

    //--------------------------------------------------------------------------
    // solid parts.
    //--------------------------------------------------------------------------

    auto solidBeamCounter = new G4Tubs(
        "BeamCounter",
        0. * cm,
        8. * cm,
        147.5 * um,
        0. * deg,
        360. * deg
    );
    auto solidMylarDegrader = new G4Tubs(
        "MylarDegrader",
        0. * cm,
        8. * cm,
        142.5 * um,
        0. * deg,
        360. * deg
    );
    auto solidSiO2Target = new G4Tubs(
        "SiO2Target",
        0. * cm,
        4. * cm,
        36.37 * um, //half width equals to 8 mg/cm2
        0. * deg,
        360. * deg
    );
    G4Tubs* solidMWPC[5];
    for (G4int chamberNb = 0; chamberNb < 5; ++chamberNb) {
        G4double radii = (8.2 + chamberNb * (32 - 8.2) / 4) * cm;
        G4double halfActiveLength = (19 + chamberNb * (40 - 19) / 4) * cm;
        solidMWPC[chamberNb] = new G4Tubs(
            "MWPC",
            radii,
            radii + 1.0 * cm,
            halfActiveLength,
            0. * deg,
            360. * deg
        );
    }
    auto solidAlSupporter = new G4Tubs(
        "AlSupporter",
        0. * cm,
        5. * cm,
        25 * um,
        0. * deg,
        360. * deg
    );
    G4Tubs* solidCollimator[8];
    for (G4int collimatorNb = 0; collimatorNb < 8; ++collimatorNb) {
        G4double radii = (5. + collimatorNb * 10.) * mm;
        G4double collilength = 40. * cm;
        solidCollimator[collimatorNb] = new G4Tubs(
            "Collimator",
            radii - 0.5 * mm,
            radii + 0.5 * mm,
            collilength,
            0. * deg,
            360. * deg
        );
    }
    auto solidCarbonFoil = new G4Tubs(
        "CarbonFoil",
        0.,
        7. * cm,
        160. * um,//0.0000964 * m
        0. * deg,
        360. * deg
    );
    auto solidMCP = new G4Tubs(
        "MCP",
        0. * cm,
        8. * cm,
        1 * cm,
        0. * deg,
        360. * deg
    );
    auto solidCsI = new G4Tubs(
        "CsI",
        8.5 * cm,
        14.5 * cm,
        14. * cm,
        0. * deg,
        360. * deg
    );
    auto solidMagneticSpectrometerShield1 = new G4Tubs(
        "MagneticSpectrometerShield1",
        40. * cm,
        45. * cm,
        50. * cm,
        0. * deg,
        360. * deg
    );
    auto solidMagneticSpectrometerShield2 = new G4Tubs(
        "MagneticSpectrometerShield2",
        8.5 * cm,
        45. * cm,
        2.5 * cm,
        0. * deg,
        360. * deg
    );
    auto solidCsIShield1 = new G4Tubs(
        "CsIShield1",
        27. * cm,
        30. * cm,
        48. * cm,
        0. * deg,
        360. * deg
    );
    auto solidCsIShield2 = new G4Tubs(
        "CsIShield2",
        0. * cm,
        27. * cm,
        1.5 * cm,
        0. * deg,
        360. * deg
    );

    //--------------------------------------------------------------------------
    // logical world.
    //--------------------------------------------------------------------------

    auto logicalWorld = new G4LogicalVolume(
        solidWorld,
        materialVacuo,
        solidWorld->GetName()
    );

    //--------------------------------------------------------------------------
    // logical fields.
    //--------------------------------------------------------------------------

    fLogicalTransportField1 = new G4LogicalVolume(
        solidTransportField1,
        materialVacuo,
        solidTransportField1->GetName()
    );
    fLogicalAcceleratorField = new G4LogicalVolume(
        solidAcceleratorField,
        materialVacuo,
        solidAcceleratorField->GetName()
    );
    fLogicalMagneticSpectrometerField = new G4LogicalVolume(
        solidMagneticSpectrometerField,
        materialVacuo,
        solidMagneticSpectrometerField->GetName()
    );
    fLogicalSeparatorField = new G4LogicalVolume(
        solidSeparatorField,
        materialVacuo,
        solidSeparatorField->GetName()
    );
    fLogicalTransportField2 = new G4LogicalVolume(
        solidTransportField2,
        materialVacuo,
        solidTransportField2->GetName()
    );
    fLogicalTransportField3 = new G4LogicalVolume(
        solidTransportField3,
        materialVacuo,
        solidTransportField3->GetName()
    );
    fLogicalCsIShellField = new G4LogicalVolume(
        solidCsIShellField,
        materialVacuo,
        solidCsIShellField->GetName()
    );

    //--------------------------------------------------------------------------
    // logical parts.
    //--------------------------------------------------------------------------

    auto logicalBeamCounter = new G4LogicalVolume(
        solidBeamCounter,
        materialPlexiGlass,
        solidBeamCounter->GetName()
    );
    auto logicalMylarDegrader = new G4LogicalVolume(
        solidMylarDegrader,
        materialMylar,
        solidMylarDegrader->GetName()
    );
    auto logicalSiO2Target = new G4LogicalVolume(
        solidSiO2Target,
        materialSiO2,
        solidSiO2Target->GetName()
    );
    for (G4int chamberNb = 0; chamberNb < 5; ++chamberNb) {
        fLogicalMWPC[chamberNb] = new G4LogicalVolume(
            solidMWPC[chamberNb],
            materialMWPC,
            solidMWPC[chamberNb]->GetName()
        );
    }
    auto logicalAlSupporter = new G4LogicalVolume(
        solidAlSupporter,
        materialAl,
        solidAlSupporter->GetName()
    );
    G4LogicalVolume* logicalCollimator[8];
    for (G4int collimatorNb = 0; collimatorNb < 8; ++collimatorNb) {
        logicalCollimator[collimatorNb] = new G4LogicalVolume(
            solidCollimator[collimatorNb],
            materialCu,
            solidCollimator[collimatorNb]->GetName()
        );
    }
    auto logicalCarbonFoil = new G4LogicalVolume(
        solidCarbonFoil,
        materialVacuo, // !!!!!!!!!!
        solidCarbonFoil->GetName()
    );
    fLogicalMCP = new G4LogicalVolume(
        solidMCP,
        materialMCP,
        solidMCP->GetName()
    );
    fLogicalCsI = new G4LogicalVolume(
        solidCsI,
        materialCsI,
        solidCsI->GetName()
    );
    auto logicalMagneticSpectrometerShield1 = new G4LogicalVolume(
        solidMagneticSpectrometerShield1,
        materialIron,
        solidMagneticSpectrometerShield1->GetName()
    );
    auto logicalMagneticSpectrometerShield2 = new G4LogicalVolume(
        solidMagneticSpectrometerShield2,
        materialIron,
        solidMagneticSpectrometerShield2->GetName()
    );
    auto logicalCsIShield1 = new G4LogicalVolume(
        solidCsIShield1,
        materialIron,
        solidCsIShield1->GetName()
    );
    auto logicalCsIShield2 = new G4LogicalVolume(
        solidCsIShield2,
        materialIron,
        solidCsIShield2->GetName()
    );

    //--------------------------------------------------------------------------
    // physical world.
    //--------------------------------------------------------------------------

    auto physicalWorld = new G4PVPlacement(
        G4Transform3D(),
        logicalWorld->GetName(),
        logicalWorld,
        nullptr,
        false, 0,
        checkSurfaceOverlaps
    );

    //--------------------------------------------------------------------------
    // physical fields.
    //--------------------------------------------------------------------------

    auto physicalTransportField1 = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0., -solidMagneticSpectrometerFieldDz + solidTransportField1Dz)
        ),
        fLogicalTransportField1->GetName(),
        fLogicalTransportField1,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    auto physicalAcceleratorField = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0., solidAcceleratorFieldDz - (8. * cos(30 * deg) + 1.) * cm)
        ),
        fLogicalAcceleratorField->GetName(),
        fLogicalAcceleratorField,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    auto physicalMagneticSpectrometerField = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector()
        ),
        fLogicalMagneticSpectrometerField->GetName(),
        fLogicalMagneticSpectrometerField,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0., 2.0 * solidAcceleratorFieldDz - (8. * cos(30 * deg) + 1.) * cm +
                solidSeparatorFieldDz)
        ),
        fLogicalSeparatorField->GetName(),
        fLogicalSeparatorField,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    fTransportField2Z = 2.0 * solidAcceleratorFieldDz - (8. * cos(30 * deg) + 1.) * cm +
        2.0 * solidSeparatorFieldDz +
        solidTransportField2->GetZHalfLength();
    new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0., fTransportField2Z)
        ),
        fLogicalTransportField2->GetName(),
        fLogicalTransportField2,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    auto physicalTransportField3 = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(G4ThreeVector(0., 1., 0.), 90 * deg),
            G4ThreeVector(solidTransportField2Dz +
                solidTransportField3Dz, 0., fTransportField2Z)
        ),
        fLogicalTransportField3->GetName(),
        fLogicalTransportField3,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    auto physicalCsIShellField = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(G4ThreeVector(0., 1., 0.), 90 * deg),
            G4ThreeVector(solidTransportField2Dz +
                2.0 * solidTransportField3Dz + solidCsIShellFieldDz, 0., fTransportField2Z)
        ),
        fLogicalCsIShellField->GetName(),
        fLogicalCsIShellField,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );

    //--------------------------------------------------------------------------
    // physical parts.
    //--------------------------------------------------------------------------

    new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0., -(8. * cos(30 * deg) + 1.) * cm - 2. * cm)
            - physicalTransportField1->GetTranslation()
        ),
        logicalBeamCounter->GetName(),
        logicalBeamCounter,
        physicalTransportField1,
        false, 0,
        checkSurfaceOverlaps
    );
    new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0., -(8. * cos(30 * deg) + 1.) * cm - 1. * cm)
            - physicalTransportField1->GetTranslation()
        ),
        logicalMylarDegrader->GetName(),
        logicalMylarDegrader,
        physicalTransportField1,
        false, 0,
        checkSurfaceOverlaps
    );
    fPhysicalSiO2Target = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(G4ThreeVector(1., 0., 0.), 60 * deg),
            G4ThreeVector() - physicalAcceleratorField->GetTranslation()
        ),
        logicalSiO2Target->GetName(),
        logicalSiO2Target,
        physicalAcceleratorField,
        false, 0,
        checkSurfaceOverlaps
    );
    for (G4int chamberNb = 0; chamberNb < 5; ++chamberNb) {
        new G4PVPlacement(
            G4Transform3D(),
            fLogicalMWPC[chamberNb]->GetName(),
            fLogicalMWPC[chamberNb],
            physicalMagneticSpectrometerField,
            true, chamberNb,
            checkSurfaceOverlaps
        );
    }
    new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(G4ThreeVector(1., 0., 0.), 60 * deg),
            G4ThreeVector(0., 0., (solidSiO2Target->GetDz() + solidAlSupporter->GetDz()) / cos(60 * deg))
            - physicalAcceleratorField->GetTranslation()
        ),
        logicalAlSupporter->GetName(),
        logicalAlSupporter,
        physicalAcceleratorField,
        false, 0,
        checkSurfaceOverlaps
    );
    for (G4int collimatorNb = 0; collimatorNb < 8; ++collimatorNb) {
        new G4PVPlacement(
            G4Transform3D(),
            logicalCollimator[collimatorNb]->GetName(),
            logicalCollimator[collimatorNb],
            physicalTransportField3,
            true, collimatorNb,
            checkSurfaceOverlaps
        );
    }
    new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0., 18.5 * cm - solidCsIShellFieldDz)
        ),
        logicalCarbonFoil->GetName(),
        logicalCarbonFoil,
        physicalCsIShellField,
        false, 0,
        checkSurfaceOverlaps
    );
    new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0., 20.0 * cm - solidCsIShellFieldDz)
        ),
        fLogicalMCP->GetName(),
        fLogicalMCP,
        physicalCsIShellField,
        false, 0,
        checkSurfaceOverlaps
    );
    new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0., 25.5 * cm - solidCsIShellFieldDz)
        ),
        fLogicalCsI->GetName(),
        fLogicalCsI,
        physicalCsIShellField,
        false, 0,
        checkSurfaceOverlaps
    );
    fPhysicalMagneticSpectrometerShield[0] = new G4PVPlacement(
        G4Transform3D(),
        logicalMagneticSpectrometerShield1->GetName(),
        logicalMagneticSpectrometerShield1,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    fPhysicalMagneticSpectrometerShield[1] = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0.,
                -solidMagneticSpectrometerShield1->GetDz() - solidMagneticSpectrometerShield2->GetDz())
        ),
        logicalMagneticSpectrometerShield2->GetName(),
        logicalMagneticSpectrometerShield2,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    fPhysicalMagneticSpectrometerShield[2] = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(),
            G4ThreeVector(0., 0.,
                solidMagneticSpectrometerShield1->GetDz() + solidMagneticSpectrometerShield2->GetDz())
        ),
        logicalMagneticSpectrometerShield2->GetName(),
        logicalMagneticSpectrometerShield2,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    fPhysicalCsIShield[0] = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(G4ThreeVector(0., 1., 0.), 90 * deg),
            physicalCsIShellField->GetTranslation()
        ),
        logicalCsIShield1->GetName(),
        logicalCsIShield1,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );
    fPhysicalCsIShield[1] = new G4PVPlacement(
        G4Transform3D(
            G4RotationMatrix(G4ThreeVector(0., 1., 0.), 90 * deg),
            physicalCsIShellField->GetTranslation() + G4ThreeVector(
                solidCsIShield1->GetDz() - solidCsIShield2->GetDz(), 0., 0.)
        ),
        logicalCsIShield2->GetName(),
        logicalCsIShield2,
        physicalWorld,
        false, 0,
        checkSurfaceOverlaps
    );

    ////////////////////////////////////////////////////////////////////////////
    //                               Cuts                                     //
    ////////////////////////////////////////////////////////////////////////////

    // Muonium production cuts, save low Energy muonium and orbit e+/e-.
    auto acceleratorFieldRegion = new G4Region("acceleratorFieldRegion");
    acceleratorFieldRegion->AddRootLogicalVolume(fLogicalAcceleratorField);
    auto acceleratorFieldRegionCuts = new G4ProductionCuts();
    acceleratorFieldRegionCuts->SetProductionCut(0., "Mu");
    acceleratorFieldRegionCuts->SetProductionCut(0.1 * eV, "e-");
    acceleratorFieldRegionCuts->SetProductionCut(0.1 * eV, "e+");
    acceleratorFieldRegion->SetProductionCuts(acceleratorFieldRegionCuts);

    return physicalWorld;
}

template<class Field_t, class Equation_t, class Stepper_t, class Driver_t>
void RegisterFields(G4LogicalVolume* logicalVolume, Field_t* field, G4double hMin, G4int nVal) {
    auto equation = new Equation_t(field);
    auto stepper = new Stepper_t(equation, nVal);
    auto driver = new Driver_t(hMin, stepper, nVal);
    auto chordFinder = new G4ChordFinder(driver);
    logicalVolume->SetFieldManager(new G4FieldManager(field, chordFinder), true);
}

void MACEDetectorConstruction::ConstructSDandField() {

    ////////////////////////////////////////////////////////////////////////////
    //                                SD                                      //
    ////////////////////////////////////////////////////////////////////////////

    auto SDManager = G4SDManager::GetSDMpointer();

    auto MCPSD = new MACEMCPSD(fLogicalMCP->GetName());
    SDManager->AddNewDetector(MCPSD);
    SetSensitiveDetector(fLogicalMCP, MCPSD);

    auto CsISD = new MACECsISD(fLogicalCsI->GetName());
    SDManager->AddNewDetector(CsISD);
    SetSensitiveDetector(fLogicalCsI, CsISD);

    auto MWPCSD = new MACEMWPCSD((*fLogicalMWPC)->GetName());
    SDManager->AddNewDetector(MWPCSD);
    for (auto MWPC : fLogicalMWPC) { SetSensitiveDetector(MWPC, MWPCSD); }

    ////////////////////////////////////////////////////////////////////////////
    //                                Field                                   //
    ////////////////////////////////////////////////////////////////////////////

    constexpr G4double hMin = 100. * um;

    RegisterFields<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fLogicalTransportField1, new G4UniformMagField(G4ThreeVector(0., 0., 0.1 * tesla)), hMin, 6);
    RegisterFields<
        MACEAcceleratorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(fLogicalAcceleratorField, new MACEAcceleratorField(), 5. * um, 8);
    RegisterFields<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fLogicalMagneticSpectrometerField, new G4UniformMagField(G4ThreeVector(0., 0., 0.1 * tesla)), hMin, 6);
    RegisterFields<
        MACESeparatorField,
        G4EqMagElectricField,
        G4DormandPrince745,
        G4IntegrationDriver<G4DormandPrince745>
    >(fLogicalSeparatorField, new MACESeparatorField(), hMin, 8);
    RegisterFields<
        MACETransportField2,
        G4TMagFieldEquation<MACETransportField2>,
        G4TDormandPrince45<G4TMagFieldEquation<MACETransportField2>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<MACETransportField2>>>
    >(fLogicalTransportField2, new MACETransportField2(fTransportField2Z), hMin, 6);
    RegisterFields<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fLogicalTransportField3, new G4UniformMagField(G4ThreeVector(0.1 * tesla, 0., 0.)), hMin, 6);
    RegisterFields<
        G4UniformMagField,
        G4TMagFieldEquation<G4UniformMagField>,
        G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>,
        G4IntegrationDriver<G4TDormandPrince45<G4TMagFieldEquation<G4UniformMagField>>>
    >(fLogicalCsIShellField, new G4UniformMagField(G4ThreeVector(0.1 * tesla, 0., 0.)), hMin, 6);
}

