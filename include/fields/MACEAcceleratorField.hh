#ifndef MACEAcceleratorField_hh
#define MACEAcceleratorField_hh 1

#include "globals.hh"
#include "G4ElectroMagneticField.hh"

class MACEAcceleratorField : public G4ElectroMagneticField {
private:
    const G4double fBz;
    const G4double fEz;

public:
    MACEAcceleratorField();
    virtual ~MACEAcceleratorField();
    virtual void GetFieldValue(const G4double point[4], double* bField) const;
    virtual G4bool DoesFieldChangeEnergy() const { return true; }
};

#endif

