#include "MACE/SimMACE/Field/SelectorField.hxx"
#include "MACE/SimMACE/Messenger/FieldMessenger.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

namespace MACE::SimMACE::Field {

using namespace MACE::Utility::LiteralUnit::ElectricFieldStrength;
using namespace MACE::Utility::LiteralUnit::Energy;
using namespace MACE::Utility::LiteralUnit::MagneticFluxDensity;
using namespace MACE::Utility::PhysicalConstant;

SelectorField::SelectorField() :
    G4ElectroMagneticField(),
    fBTransport(0.1_T),
    fSelectEk(7_keV),
    fESelect(5_kV_cm),
    fBSelect(fESelect / c_light * std::sqrt(electron_mass_c2 / (2 * fSelectEk))) {
    Messenger::FieldMessenger::Instance().SetTo(this);
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
    fBSelect = E / c_light * std::sqrt(electron_mass_c2 / (2 * fSelectEk));
}

void SelectorField::SetSelectEnergy(G4double Ek) {
    fSelectEk = Ek;
    fESelect = c_light * std::sqrt(2 * fSelectEk / electron_mass_c2) * fBSelect;
}

} // namespace MACE::SimMACE::Field
