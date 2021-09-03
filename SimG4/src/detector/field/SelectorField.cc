#include "detector/field/SelectorField.hh"
#include "messenger/FieldMessenger.hh"

using namespace MACE::SimG4::Field;

SelectorField::SelectorField() :
    G4ElectroMagneticField() {
    FieldMessenger::Instance()->Set(this);
}

void SelectorField::GetFieldValue(const G4double*, G4double* F) const {
    F[0] = fBx;
    F[1] = 0.;
    F[2] = fBz;
    F[3] = 0.;
    F[4] = fEy;
    F[5] = 0.;
}

void SelectorField::SetSelectorMagneticField(G4double B) {
    fBx = B;
    fEy = -c_light * sqrt(2.0 * fSelectEk / G4Positron::Definition()->GetPDGMass()) * fBx;
}

void SelectorField::SetSelectEnergy(G4double Ek) {
    fSelectEk = Ek;
    fEy = -c_light * sqrt(2.0 * fSelectEk / G4Positron::Definition()->GetPDGMass()) * fBx;
}
