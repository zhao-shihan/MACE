#include "SimG4/field/SecondBendField.hh"
#include "SimG4/messenger/FieldMessenger.hh"

using namespace MACE::SimG4::Field;

SecondBendField::SecondBendField() :
    G4MagneticField() {
    Messenger::FieldMessenger::Instance()->Set(this);
}

void SecondBendField::GetFieldValue(const G4double* x, G4double* B) const {
    G4double r = sqrt((x[0] - fXc) * (x[0] - fXc) + (x[2] - fZc) * (x[2] - fZc));
    B[0] = -(x[2] - fZc) / r * fB;
    B[1] = 0.;
    B[2] = (x[0] - fXc) / r * fB;
}
