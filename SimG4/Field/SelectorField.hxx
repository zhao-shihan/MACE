#pragma once

#include "G4ElectroMagneticField.hh"
#include "G4Positron.hh"

#include "SimG4/Global.hxx"

class MACE::SimG4::Field::SelectorField : public G4ElectroMagneticField {
public:
    SelectorField();
    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetSelectorMagneticField(G4double B);
    void SetTransportField(G4double B) { fBTransport = B; }
    void SetSelectEnergy(G4double Ek);

private:
    G4double fBSelect = 0.01 * tesla;
    G4double fBTransport = 0.1 * tesla;
    G4double fESelect = c_light * sqrt(2.0 * 7 * keV / G4Positron::Definition()->GetPDGMass()) * fBSelect;

    G4double fSelectEk = 7 * keV;
};
