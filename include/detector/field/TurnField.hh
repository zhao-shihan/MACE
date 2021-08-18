#pragma once

#include "G4MagneticField.hh"

#include "MACEGlobal.hh"

class MACE::Field::TurnField : public G4MagneticField {
public:
    TurnField();
    virtual void GetFieldValue(const G4double* x, G4double* B) const;

private:
    const G4double fBz = 0.1 * tesla;
};
