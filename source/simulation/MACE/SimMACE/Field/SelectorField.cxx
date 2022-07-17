#include "MACE/SimMACE/Field/SelectorField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"

#include "G4PhysicalConstants.hh"

namespace MACE::SimMACE::Field {

using Messenger::FieldMessenger;
using namespace MACE::Utility::LiteralUnit::ElectricFieldStrength;
using namespace MACE::Utility::LiteralUnit::Energy;
using namespace MACE::Utility::LiteralUnit::MagneticFluxDensity;

SelectorField::SelectorField() :
    G4ElectroMagneticField(),
    fBTransport(0.1_T),
    fSelectEk(7_keV),
    fESelect(5_kV_cm),
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

} // namespace MACE::SimMACE::Field
