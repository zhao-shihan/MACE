#pragma once

#include "G4ElectroMagneticField.hh"

#include "SimG4Global.hh"


class MACE::SimG4::Field::AcceleratorField : public G4ElectroMagneticField {
public:
    AcceleratorField();
    virtual void GetFieldValue(const G4double*, G4double* F) const;
    virtual G4bool DoesFieldChangeEnergy() const { return true; }

private:
    const G4double fBz = 0.1 * tesla;
    const G4double fEz = 7 * kilovolt / (30 * cm);
};
