#include "detector/field/AcceleratorField.hh"

MACE::Field::AcceleratorField::AcceleratorField() :
    G4ElectroMagneticField() {}

void MACE::Field::AcceleratorField::GetFieldValue(const G4double*, G4double* F) const {
    F[0] = 0.;
    F[1] = 0.;
    F[2] = fBz;
    F[3] = 0.;
    F[4] = 0.;
    F[5] = fEz;
}
