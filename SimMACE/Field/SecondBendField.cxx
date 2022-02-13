#include "SimMACE/Field/SecondBendField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using namespace MACE::SimMACE::Field;

SecondBendField::SecondBendField() :
    G4MagneticField() {
    Messenger::FieldMessenger::Instance().Set(this);
}

void SecondBendField::GetFieldValue(const G4double* x, G4double* B) const {
    G4double r = sqrt((x[0] - fXc) * (x[0] - fXc) + (x[2] - fZc) * (x[2] - fZc));
    B[0] = -(x[2] - fZc) / r * fB;
    B[1] = 0.;
    B[2] = (x[0] - fXc) / r * fB;
}
