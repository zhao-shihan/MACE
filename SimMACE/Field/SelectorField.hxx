#pragma once

#include "G4ElectroMagneticField.hh"
#include "G4Positron.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Field::SelectorField final :
    public G4ElectroMagneticField {
public:
    SelectorField();
    ~SelectorField() noexcept = default;
    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetTransportField(G4double B) { fBTransport = B; }
    void SetSelectorMagneticField(G4double B);
    void SetSelectEnergy(G4double Ek);

private:
    G4double fBTransport = 0.1_T;
    G4double fBSelect = 0.01_T;
    G4double fESelect = CLHEP::c_light * std::sqrt(2 * 7_keV / G4Positron::Definition()->GetPDGMass()) * fBSelect;

    G4double fSelectEk = 7_keV;
};
