#include "G4PhysicalConstants.hh"

#include "SimMACE/Field/SelectorField.hxx"
#include "SimMACE/Messenger/FieldMessenger.hxx"

using namespace MACE::SimMACE::Field;

SelectorField::SelectorField() :
    G4ElectroMagneticField(),
    fBSelect(fESelect / c_light * std::sqrt(G4Positron::Definition()->GetPDGMass() / (2 * fSelectEk))) {
    FieldMessenger::Instance().Set(this);
}

void SelectorField::GetFieldValue(const G4double*, G4double* F) const {
    F[0] = fBTransport;
    F[1] = 0;
    F[2] = fBSelect;
    F[3] = 0;
    F[4] = fESelect;
    F[5] = 0;
}

void SelectorField::SetSelectorElectricField(G4double E) {
    fESelect = E;
    fBSelect = E / c_light * std::sqrt(G4Positron::Definition()->GetPDGMass() / (2 * fSelectEk));
}

void SelectorField::SetSelectEnergy(G4double Ek) {
    fSelectEk = Ek;
    fESelect = c_light * std::sqrt(2 * fSelectEk / G4Positron::Definition()->GetPDGMass()) * fBSelect;
}
