#include "detector/field/TurnField.hh"

MACE::Field::TurnField::TurnField() :
    G4MagneticField() {}

void MACE::Field::TurnField::GetFieldValue(const G4double* x, G4double* B) const {
    constexpr G4double x0 = 30 * cm;
    constexpr G4double z0 = 140 * cm;
    G4double r = sqrt((x[0] - x0) * (x[0] - x0) + (x[2] - z0) * (x[2] - z0));
    B[0] = (x[2] - z0) / r * fBz;
    B[1] = 0.;
    B[2] = -(x[0] - x0) / r * fBz;
}
