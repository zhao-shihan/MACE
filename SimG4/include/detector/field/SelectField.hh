#pragma once

#include "G4ElectroMagneticField.hh"

#include "SimG4Global.hh"


class MACE::SimG4::Field::SelectField : public G4ElectroMagneticField {
public:
    SelectField();
    virtual void GetFieldValue(const G4double*, G4double* F) const;
    virtual G4bool DoesFieldChangeEnergy() const { return true; }

private:
    const G4double fEkin = 7 * keV;
    const G4double fBx = 0.1 * tesla;
    const G4double fBz = 0.1 * tesla;
    const G4double fEy;
};
