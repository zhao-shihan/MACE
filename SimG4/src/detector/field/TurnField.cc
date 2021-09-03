#include "detector/field/TurnField.hh"
#include "messenger/FieldMessenger.hh"

using namespace MACE::SimG4::Field;

TurnField::TurnField() :
    G4MagneticField() {
    FieldMessenger::Instance()->Set(this);
}

void TurnField::GetFieldValue(const G4double* x, G4double* B) const {
    G4double r = sqrt((x[0] - fXc) * (x[0] - fXc) + (x[2] - fZc) * (x[2] - fZc));
    B[0] = (x[2] - fZc) / r * fB;
    B[1] = 0.;
    B[2] = -(x[0] - fXc) / r * fB;
}
