#ifndef MACEDetectorConstruction_h
#define MACEDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4PVPlacement.hh"

class MACEDetectorConstruction : public G4VUserDetectorConstruction {
private:
    G4LogicalVolume* fLogicalMWPC[5];
    G4LogicalVolume* fLogicalMCP;
    G4LogicalVolume* fLogicalCsI;

    G4LogicalVolume* fLogicalTransportField1;
    G4LogicalVolume* fLogicalAcceleratorField;
    G4LogicalVolume* fLogicalMagneticSpectrometerField;
    G4LogicalVolume* fLogicalSeparatorField;
    G4LogicalVolume* fLogicalTransportField2;
    G4LogicalVolume* fLogicalTransportField3;
    G4LogicalVolume* fLogicalCsIShellField;

    G4double fTransportField2Z;

    G4PVPlacement* fPhysicalSiO2Target;
    G4PVPlacement* fPhysicalMagneticSpectrometerShield[3];
    G4PVPlacement* fPhysicalCsIShield[2];

public:
    MACEDetectorConstruction();
    virtual ~MACEDetectorConstruction();
    virtual G4VPhysicalVolume* Construct();
    virtual void ConstructSDandField();

    auto GetPhysicalSiO2Target() const { return fPhysicalSiO2Target; }
    auto GetPhysicalMagneticSpectrometerShield() const { return fPhysicalMagneticSpectrometerShield; }
    auto GetPhysicalCsIShield() const { return fPhysicalCsIShield; }
};

#endif
