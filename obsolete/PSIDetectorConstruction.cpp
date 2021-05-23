// PSIMACEDetectorConstruction
//
// Author:	Yuzhe Mao 02.2020
//
// Review and update: Shihan Zhao 05.2021
// 
// Simulation of PSIMACE Muonium-AntiMuonium Conversion Expriment Detector
// Missing collimator and beam counter.


#include "userAction/PSIMACEDetectorConstruction.hh"
#include "SD/PSIMACEMCPSD.hh"
#include "SD/PSIMACECsISD.hh"
#include "PSIMACEMagSpectrometerSD.hh"
#include "PSIMACETransMagField.hh"
#include "PSIMACESelectMagField.hh"
#include "fields/PSIMACESeparatorField.hh"

#include "G4NistManager.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"
#include "G4Mag_UsualEqRhs.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"
#include "G4UserLimits.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4AutoDelete.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4SystemOfUnits.hh"
#include "G4Colour.hh"
#include "G4EqMagElectricField.hh"
#include "G4DormandPrince745.hh"
#include "G4MagIntegratorStepper.hh"
#include "G4MagIntegratorDriver.hh"
#include "G4ChordFinder.hh"

G4ThreadLocal PSIMACETransMagField* PSIMACEDetectorConstruction::fAcceElecField = 0;
G4ThreadLocal PSIMACESelectMagField* PSIMACEDetectorConstruction::fSelectMagField = 0;
G4ThreadLocal G4UniformMagField* PSIMACEDetectorConstruction::fSpecMagField = 0;
G4ThreadLocal G4UniformMagField* PSIMACEDetectorConstruction::fTransSecondField = 0;
G4ThreadLocal PSIMACESeparatorField* PSIMACEDetectorConstruction::fSeparatorField = 0;

G4ThreadLocal G4FieldManager* PSIMACEDetectorConstruction::fFieldMgr1 = 0;
G4ThreadLocal G4FieldManager* PSIMACEDetectorConstruction::fFieldMgr2 = 0;
G4ThreadLocal G4FieldManager* PSIMACEDetectorConstruction::fFieldMgr3 = 0;
G4ThreadLocal G4FieldManager* PSIMACEDetectorConstruction::fFieldMgr4 = 0;
G4ThreadLocal G4FieldManager* PSIMACEDetectorConstruction::fFieldMgr5 = 0;

PSIMACEDetectorConstruction::PSIMACEDetectorConstruction() :
    G4VUserDetectorConstruction(),
    SiO2(nullptr),
    Vacuo(nullptr),
    Al(nullptr),
    Cu(nullptr),
    carbon(nullptr),
    MgO(nullptr),
    CsI(nullptr),
    PGlass(nullptr),
    Iron(nullptr),
    Mylar(nullptr),
    fSupAngle(30. * deg),
    fSupRotation(new G4RotationMatrix()),
    fSpeAngle(90. * deg),
    fSpeRotation(new G4RotationMatrix()),
    fShiRotation(new G4RotationMatrix()),
    fTopRotation(new G4RotationMatrix()),
    SelectMagLog(nullptr),
    AcceElecLog(nullptr),
    SeparatorLog(nullptr),
    MagLog(nullptr),
    TransSecondLog(nullptr),
    fSpectrometer(new G4LogicalVolume* [5]),
    fCollimator(new G4LogicalVolume* [8]),
    fKineticEnergyLimit(nullptr),
    fCheckOverlaps(true) {

    fSupRotation->rotateX(fSupAngle);
    fSpeRotation->rotateX(fSpeAngle);
    fShiRotation->rotateY(fSpeAngle);
    fTopRotation->rotateX(fSpeAngle);
}

PSIMACEDetectorConstruction::~PSIMACEDetectorConstruction() {
    delete fSupRotation;
    delete fSpeRotation;
    delete fShiRotation;
    delete fTopRotation;
    delete[] fSpectrometer;
    delete[] fCollimator;
}

void PSIMACEDetectorConstruction::DefineMaterials() {
    G4NistManager* nistManager = G4NistManager::Instance();

    SiO2 = nistManager->FindOrBuildMaterial("G4_SILICON_DIOXIDE");
    Vacuo = nistManager->FindOrBuildMaterial("G4_Galactic");
    Al = nistManager->FindOrBuildMaterial("G4_Al");
    Cu = nistManager->FindOrBuildMaterial("G4_Cu");
    carbon = nistManager->FindOrBuildMaterial("G4_C");
    CsI = nistManager->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    PGlass = nistManager->FindOrBuildMaterial("G4_PLEXIGLASS");
    MgO = nistManager->FindOrBuildMaterial("G4_MAGNESIUM_OXIDE");
    Iron = nistManager->FindOrBuildMaterial("G4_Pb");
    Mylar = nistManager->FindOrBuildMaterial("G4_MYLAR");
}

G4VPhysicalVolume* PSIMACEDetectorConstruction::Construct() {
    DefineMaterials();
    return DefineVolumes();
}

G4VPhysicalVolume* PSIMACEDetectorConstruction::DefineVolumes() {
    G4double world_hx = 3.0 * m;
    G4double world_hy = 3.0 * m;
    G4double world_hz = 3.0 * m;

    G4Box* worldBox
        = new G4Box("World", world_hx, world_hy, world_hz);

    G4Tubs* solidSiO2Target
        = new G4Tubs("SiO2Target", 0. * m, 0.08 * m, 36.37 * um, 0. * deg, 360. * deg);//half width equals to 8 mg/cm2

    G4Tubs* ScintCounterTubs
        = new G4Tubs("ScintCounter", 0. * m, 0.08 * m, 147.5 * um, 0. * deg, 360. * deg);

    G4Tubs* MylarDegraderTubs
        = new G4Tubs("MylarDegrader", 0. * m, 0.08 * m, 142.5 * um, 0. * deg, 360. * deg);

    G4Tubs* AlSupporterTubs
        = new G4Tubs("AlSupporter", 0. * m, 0.08 * m, 25 * um, 0. * deg, 360. * deg);

    G4Tubs* solidGuidanceMagneticField
        = new G4Tubs("SelectionMagnetic", 0., 0.35 * m, 0.1 * m, 0. * deg, 360. * deg);

    G4Tubs* AcceElectronTubs
        = new G4Tubs("AcceElectron", 0. * m, 0.08 * m, 0.2 * m, 0. * deg, 360. * deg);

    G4Tubs* SeparatorTubs
        = new G4Tubs("MuonSeparator", 0. * m, 0.08 * m, 0.25 * m, 0. * deg, 360. * deg);

    G4Tubs* TransSecondTubs
        = new G4Tubs("TransMagSecond", 0. * m, 0.16 * m, 0.65 * m, 0. * deg, 360. * deg);

    G4Tubs* MCPTubs
        = new G4Tubs("MCPBox", 0. * m, 0.08 * m, 0.05 * m, 0. * deg, 360. * deg);

    G4Tubs* solidCarbonFoil
        = new G4Tubs("MgOEmi", 0., 0.07 * m, 0.0000964 * m, 0. * deg, 360. * deg);

    G4Tubs* CsIScintTubs
        = new G4Tubs("CsIScint", 0.0845 * m, 0.1 * m, 0.25 * m, 0. * deg, 360. * deg);

    G4Tubs* solidIronShield1
        = new G4Tubs("IronShield1", 0.0845 * m, 0.15 * m, 0.65 * m, 0. * deg, 360. * deg);

    G4Tubs* solidIronShield2
        = new G4Tubs("IronShield2", 35.0 * cm, 37.0 * cm, 45.0 * cm, 0. * deg, 360. * deg);

    G4Tubs* MagBox
        = new G4Tubs("MagBox", 8.2 * cm, 37.0 * cm, 47.0 * cm, 0. * deg, 360. * deg);//

    G4Tubs* solidIronShield3
        = new G4Tubs("IronShield3", 0.085 * m, 0.35 * m, 0.02 * m, 0. * deg, 360. * deg);

    //------------------------------LogicalVolume-------------------------------------------------------------
    G4LogicalVolume* logicalWorld
        = new G4LogicalVolume(worldBox, Vacuo, "World");

    G4LogicalVolume* ScintCounterLog
        = new G4LogicalVolume(ScintCounterTubs, PGlass, "ScintCounterLog");

    fLogicalTarget
        = new G4LogicalVolume(solidSiO2Target, carbon, "SiO2TargetLog");

    G4LogicalVolume* MylarDegraderLog
        = new G4LogicalVolume(MylarDegraderTubs, Mylar, "MylarDegraderLog");

    G4LogicalVolume* AlSupporterLog
        = new G4LogicalVolume(AlSupporterTubs, Vacuo, "AlSupporter");

    G4LogicalVolume* MCPLog
        = new G4LogicalVolume(MCPTubs, MgO, "MCPLog");

    G4LogicalVolume* MgOEmiLog
        = new G4LogicalVolume(solidCarbonFoil, carbon, "MgOEmiLog");

    G4LogicalVolume* CsIScintLog
        = new G4LogicalVolume(CsIScintTubs, CsI, "CsIScintLog");

    G4LogicalVolume* IronShieldLog1
        = new G4LogicalVolume(solidIronShield1, Iron, "IronShieldLog1");//for positron Detector

    G4LogicalVolume* IronShieldLog2
        = new G4LogicalVolume(solidIronShield2, Iron, "IronShieldLog2");//both for electron Detector

    G4LogicalVolume* IronShieldLog3
        = new G4LogicalVolume(solidIronShield3, Iron, "IronShieldLog3");


    // Logical Volume for EMFields
    // SelectLog, only allow e+ with kinetic energy of 7keV into next Log.r=35cm.
    // TransLog, second part of e+ tranportation, first part is AcceElecLog.
    TransSecondLog = new G4LogicalVolume(TransSecondTubs, Vacuo, "TransSecondLog");

    SelectMagLog = new G4LogicalVolume(solidGuidanceMagneticField, Vacuo, "SelectMagLog");

    // Region of Spectrometer and SiO2 Target. 
    // In theory Muonium-AntiMuonium conversion will happened in much lower probability with Magnetic Filed, ignore it.

    //	Entire EletricMagFiled Log for MagSpectrometer,
    // when registing MagField, set the parameter as false(unvalid) for daughter LogicalVolume.
    // so outside the AcceElecLog, there is only MagField, which is used for high energy e- detection.
    MagLog = new G4LogicalVolume(MagBox, Vacuo, "MagLog");

    // Both Electric Field and Magnetic Filed registed to this Log
    AcceElecLog = new G4LogicalVolume(AcceElectronTubs, Vacuo, "AcceElecLog");

    SeparatorLog = new G4LogicalVolume(SeparatorTubs, Vacuo, "SeparatorLog");

    // Production Cuts, dont kill low Energy e- and e+.
    G4Region* myRegion = new G4Region("AcceElecLogRegion");
    myRegion->AddRootLogicalVolume(AcceElecLog);
    G4ProductionCuts* cuts = new G4ProductionCuts();
    // cuts->SetProductionCut(1 * eV, "e+");
    // cuts->SetProductionCut(1 * eV, "e-");
    cuts->SetProductionCut(0., "Mu");
    myRegion->SetProductionCuts(cuts);



    //--------------------------------------------------PVPlacement-------------------------------------------------------------
    G4VPhysicalVolume* worldPV
        = new G4PVPlacement(0, G4ThreeVector(), logicalWorld,
            "World", 0, false, 0, fCheckOverlaps);

    new G4PVPlacement(fSpeRotation, G4ThreeVector(0., -0.39 * m, 0.), MagLog, "MagG", logicalWorld, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0., 0.83 * m, 0.), SelectMagLog, "SelectMag", logicalWorld, false, 0, fCheckOverlaps);

    new G4PVPlacement(fSpeRotation, G4ThreeVector(0., 0.23 * m, 0.), SeparatorLog, "Separator", logicalWorld, false, 0, fCheckOverlaps);

    new G4PVPlacement(fSpeRotation, G4ThreeVector(0., -0.22 * m, 0.), AcceElecLog, "AcceElec", logicalWorld, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0., 0., -0.198 * m), fLogicalTarget, "SiO2Target", AcceElecLog, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0., 0., -0.1985 * m), AlSupporterLog, "AlSupporter", AcceElecLog, false, 0, fCheckOverlaps);

    new G4PVPlacement(fSpeRotation, G4ThreeVector(0., -0.43 * m, 0), MylarDegraderLog, "MylarDegrader", logicalWorld, false, 0, fCheckOverlaps);

    new G4PVPlacement(fSpeRotation, G4ThreeVector(0., -0.44 * m, 0), ScintCounterLog, "ScintCounter", logicalWorld, false, 0, fCheckOverlaps);

    //   new G4PVPlacement(0,G4ThreeVector(0.55*m,0.83*m,0.),SelectMagLog,"SelectMag",logicalWorld,false,0,fCheckOverlaps);

    new G4PVPlacement(fShiRotation, G4ThreeVector(1.0 * m, 0.83 * m, 0.), TransSecondLog, "TransMagSecond", logicalWorld, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(), IronShieldLog1, "IronShield1", TransSecondLog, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0., 0., -20.0 * cm), CsIScintLog, "CsIScint", IronShieldLog1, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0., 0., -20.0 * cm), MCPLog, "MCPDetector", TransSecondLog, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0., 0., -0.2505 * m), MgOEmiLog, "MgOEmitter", TransSecondLog, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(), IronShieldLog2, "IronShield2", MagLog, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0., 0., 0.45 * m), IronShieldLog3, "IronShield3", MagLog, false, 0, fCheckOverlaps);

    new G4PVPlacement(0, G4ThreeVector(0., 0., -0.45 * m), IronShieldLog3, "IronShield3", MagLog, false, 0, fCheckOverlaps);


    //Collimator Construction
    for (G4int copynumb = 0; copynumb < 8; copynumb++) {
        G4double radii = (5.0 + copynumb * 10) * mm;
        G4double collilength = 30 * cm;

        G4Tubs* ColliTub
            = new G4Tubs("Colli", radii - 0.5 * mm, radii + 0.5 * mm, collilength, 0. * deg, 360. * deg);

        fCollimator[copynumb]
            = new G4LogicalVolume(ColliTub, Cu, "fCollimator");//Copper Collimator 

        new G4PVPlacement(0, G4ThreeVector(0., 0., 0.35 * m), fCollimator[copynumb], "Collimator", TransSecondLog, false, 0, fCheckOverlaps);
    }


    //Magnetic Spectrometer Construction
    for (G4int copynumb = 0; copynumb < 5; copynumb++) {
        G4double radii = (8.2 + copynumb * (32 - 8.2) / 4) * cm;
        G4double activelength = (19 + copynumb * (40 - 19) / 4) * cm;

        G4Tubs* MagSpectroTub
            = new G4Tubs("Spec", radii, radii + 1.0 * cm, activelength, 0. * deg, 360. * deg);

        fSpectrometer[copynumb]
            = new G4LogicalVolume(MagSpectroTub, SiO2, "fSpectrometer");

        new G4PVPlacement(0, G4ThreeVector(), fSpectrometer[copynumb], "MagSpectrometer", MagLog, true, copynumb, fCheckOverlaps);
    }

    return worldPV;
}


void PSIMACEDetectorConstruction::SetCheckOverlaps(G4bool checkOverlaps) {
    fCheckOverlaps = checkOverlaps;
}

#include "G4RK547FEq1.hh"

void PSIMACEDetectorConstruction::ConstructSDandField() {
    // Setting Sensitive detectors
    G4String fSDname1 = "PSIMACE/CsISD";
    PSIMACECsISD* fCsISD = new PSIMACECsISD(fSDname1);
    G4SDManager::GetSDMpointer()->AddNewDetector(fCsISD);
    SetSensitiveDetector("CsIScintLog", fCsISD, true);

    G4String fSDname2 = "PSIMACE/MCPSD";
    PSIMACEMCPSD* fMCPSD = new PSIMACEMCPSD(fSDname2);
    G4SDManager::GetSDMpointer()->AddNewDetector(fMCPSD);
    SetSensitiveDetector("MCPLog", fMCPSD, true);

    G4String fSDname3 = "PSIMACE/MagSpectrometerSD";
    PSIMACEMagSpectrometerSD* fMagSD = new PSIMACEMagSpectrometerSD(fSDname3);
    G4SDManager::GetSDMpointer()->AddNewDetector(fMagSD);
    SetSensitiveDetector("fSpectrometer", fMagSD, true);


    // Pure Magnetic field ,deflects most of mu+ and ions with positive charge.
    // inherit from G4ElectroMagneticField
    fSelectMagField = new PSIMACESelectMagField();
    fFieldMgr1 = new G4FieldManager();
    fFieldMgr1->SetDetectorField(fSelectMagField);
    fFieldMgr1->CreateChordFinder(fSelectMagField);
    SelectMagLog->SetFieldManager(fFieldMgr1, true);

    // AcceElectricfield, with 0.1T Magfield.
    fAcceElecField = new PSIMACETransMagField();
    fFieldMgr2 = new G4FieldManager();
    fEquation = new G4EqMagElectricField(fAcceElecField);
    fStepper = new G4DormandPrince745(fEquation, 8);
    fFieldMgr2->SetDetectorField(fAcceElecField);
    fIntgrDriver = new G4MagInt_Driver(0.1 * mm,
        fStepper,
        fStepper->GetNumberOfVariables());
    fChordFinder = new G4ChordFinder(fIntgrDriver);
    fFieldMgr2->SetChordFinder(fChordFinder);
    AcceElecLog->SetFieldManager(fFieldMgr2, true);

    // MagField for MagSpectrometer.
    fSpecMagField = new G4UniformMagField(G4ThreeVector(0.0, 0.1 * tesla, 0.0));
    fFieldMgr3 = new G4FieldManager();
    fFieldMgr3->SetDetectorField(fSpecMagField);
    fFieldMgr3->CreateChordFinder(fSpecMagField);
    MagLog->SetFieldManager(fFieldMgr3, true);

    // MagField, Second part of e+ Tranportation.
    fTransSecondField = new G4UniformMagField(G4ThreeVector(0.1 * tesla, 0.0, 0.0));
    fFieldMgr4 = new G4FieldManager();
    fFieldMgr4->SetDetectorField(fTransSecondField);
    fFieldMgr4->CreateChordFinder(fTransSecondField);
    TransSecondLog->SetFieldManager(fFieldMgr4, true);

    fSeparatorField = new PSIMACESeparatorField();
    fFieldMgr5 = new G4FieldManager();
    fEquation = new G4EqMagElectricField(fSeparatorField);
    fStepper = new G4DormandPrince745(fEquation, 8);
    fFieldMgr5->SetDetectorField(fSeparatorField);
    fIntgrDriver = new G4MagInt_Driver(0.1 * mm,
        fStepper,
        fStepper->GetNumberOfVariables());
    fChordFinder = new G4ChordFinder(fIntgrDriver);
    fFieldMgr5->SetChordFinder(fChordFinder);
    SeparatorLog->SetFieldManager(fFieldMgr5, true);
}

