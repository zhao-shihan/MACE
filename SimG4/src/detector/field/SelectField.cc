#include "detector/field/SelectField.hh"

MACE::SimG4::Field::SelectField::SelectField() :
    G4ElectroMagneticField(),
    fEy(-c_light * sqrt(1 - 1 / ((1 + 511 * keV / fEkin) * (1 + 511 * keV / fEkin))) * fBx) {}

void MACE::SimG4::Field::SelectField::GetFieldValue(const G4double*, G4double* F) const {
    F[0] = fBx;
    F[1] = 0.;
    F[2] = fBz;
    F[3] = 0.;
    F[4] = fEy;
    F[5] = 0.;
}
