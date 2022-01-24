#include "SimMACE/Field/FirstBendField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using namespace MACE::SimMACE::Field;

FirstBendField::FirstBendField() :
    G4MagneticField() {
    Messenger::FieldMessenger::Instance()->Set(this);
}

void FirstBendField::GetFieldValue(const G4double* x, G4double* B) const {
    G4double r = sqrt((x[0] - fXc) * (x[0] - fXc) + (x[2] - fZc) * (x[2] - fZc));
    B[0] = (x[2] - fZc) / r * fB;
    B[1] = 0.;
    B[2] = -(x[0] - fXc) / r * fB;
}
