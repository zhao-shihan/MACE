#ifndef PSIMACEDetectorConstruction_h
#define PSIMACEDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4RotationMatrix.hh"
#include "G4FieldManager.hh"
#include "G4UniformMagField.hh"

class PSIMACETransMagField;
class PSIMACESelectMagField;
class PSIMACESeparatorField;

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;

class G4EqMagElectricField;
class G4MagIntegratorStepper;
class G4MagInt_Driver;
class G4FieldManager;
class G4ChordFinder;

class PSIMACEDetectorConstruction : public G4VUserDetectorConstruction {
private:
    static G4ThreadLocal PSIMACETransMagField* fAcceElecField;
    static G4ThreadLocal PSIMACESelectMagField* fSelectMagField;
    static G4ThreadLocal G4UniformMagField* fSpecMagField;
    static G4ThreadLocal G4UniformMagField* fTransSecondField;
    static G4ThreadLocal PSIMACESeparatorField* fSeparatorField;

    static G4ThreadLocal G4FieldManager* fFieldMgr1;
    static G4ThreadLocal G4FieldManager* fFieldMgr2;
    static G4ThreadLocal G4FieldManager* fFieldMgr3;
    static G4ThreadLocal G4FieldManager* fFieldMgr4;
    static G4ThreadLocal G4FieldManager* fFieldMgr5;

    G4Material* SiO2;
    G4Material* Vacuo;
    G4Material* Al;
    G4Material* Cu;
    G4Material* carbon;
    G4Material* MgO;
    G4Material* CsI;
    G4Material* PGlass;
    G4Material* Iron;
    G4Material* Mylar;

    G4EqMagElectricField* fEquation;
    G4MagIntegratorStepper* fStepper;
    G4MagInt_Driver* fIntgrDriver;
    G4ChordFinder* fChordFinder;

    G4double fSupAngle;
    G4RotationMatrix* fSupRotation;
    G4double fSpeAngle;
    G4RotationMatrix* fSpeRotation;
    G4RotationMatrix* fShiRotation;
    G4RotationMatrix* fTopRotation;

    G4LogicalVolume* SelectMagLog;//SelectMag
    G4LogicalVolume* AcceElecLog;//TransMag
    G4LogicalVolume* SeparatorLog;
    G4LogicalVolume* MagLog;//SpecMag
    G4LogicalVolume* TransSecondLog;//TransSecondMag

    G4LogicalVolume** fSpectrometer;
    G4LogicalVolume** fCollimator;

    G4UserLimits* fKineticEnergyLimit;

    G4bool fCheckOverlaps;

    G4LogicalVolume* fLogicalTarget;

public:
    PSIMACEDetectorConstruction();
    virtual ~PSIMACEDetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    void SetMaxStep(G4double);
    void SetCheckOverlaps(G4bool);

    auto GetLogicalTarget() const { return fLogicalTarget; }

private:
    void DefineMaterials();
    G4VPhysicalVolume* DefineVolumes();
};

#endif
