#include "detector/field/FirstBendField.hh"
#include "messenger/FieldMessenger.hh"

using namespace MACE::SimG4::Field;

FirstBendField::FirstBendField() :
    G4MagneticField() {
    FieldMessenger::Instance()->Set(this);
}

void FirstBendField::GetFieldValue(const G4double* x, G4double* B) const {
    G4double r = sqrt((x[0] - fXc) * (x[0] - fXc) + (x[2] - fZc) * (x[2] - fZc));
    B[0] = (x[2] - fZc) / r * fB;
    B[1] = 0.;
    B[2] = -(x[0] - fXc) / r * fB;
}
