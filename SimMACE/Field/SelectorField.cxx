#include "SimMACE/Field/SelectorField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using namespace MACE::SimMACE::Field;

SelectorField::SelectorField() :
    G4ElectroMagneticField() {
    Messenger::FieldMessenger::Instance()->Set(this);
}

void SelectorField::GetFieldValue(const G4double*, G4double* F) const {
    F[0] = fBTransport;
    F[1] = 0.;
    F[2] = fBSelect;
    F[3] = 0.;
    F[4] = fESelect;
    F[5] = 0.;
}

void SelectorField::SetSelectorMagneticField(G4double B) {
    fBSelect = B;
    fESelect = -c_light * sqrt(2.0 * fSelectEk / G4Positron::Definition()->GetPDGMass()) * fBSelect;
}

void SelectorField::SetSelectEnergy(G4double Ek) {
    fSelectEk = Ek;
    fESelect = -c_light * sqrt(2.0 * fSelectEk / G4Positron::Definition()->GetPDGMass()) * fBSelect;
}
