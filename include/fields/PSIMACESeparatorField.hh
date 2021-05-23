#ifndef G4ElectroMagneticField_hh
#define G4ElectroMagneticField_hh 1

#include "globals.hh"
#include "G4ElectroMagneticField.hh"

class PSIMACESeparatorField : public G4ElectroMagneticField {
private:
    const G4double fBy;
    const G4double fBz;
    const G4double fEx;

public:
    PSIMACESeparatorField();
    virtual ~PSIMACESeparatorField();
    virtual void GetFieldValue(const G4double point[4], double* bField) const;
    virtual G4bool DoesFieldChangeEnergy() const { return true; }
};

#endif

