#pragma once

#include "Utility/LiteralUnit.hxx"
#include "Simulation/SimMACE/Global.hxx"

#include "G4ElectroMagneticField.hh"
#include "G4Positron.hh"

namespace MACE::Simulation::SimMACE::Field {

class SelectorField final : public G4ElectroMagneticField {
public:
    SelectorField();
    ~SelectorField() noexcept = default;
    SelectorField(const SelectorField&) = delete;
    SelectorField& operator=(const SelectorField&) = delete;

    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetTransportField(G4double B) { fBTransport = B; }
    void SetSelectorElectricField(G4double E);
    void SetSelectEnergy(G4double Ek);

private:
    G4double fBTransport;
    G4double fSelectEk;
    G4double fESelect;
    G4double fBSelect;
};

} // namespace MACE::Simulation::SimMACE::Field
