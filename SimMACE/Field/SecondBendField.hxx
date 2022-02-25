#pragma once

#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Field::SecondBendField final :
    public G4MagneticField {
public:
    SecondBendField();
    ~SecondBendField() noexcept = default;
    void GetFieldValue(const G4double* x, G4double* B) const override;

    void SetTransportMagneticField(G4double B) { fB = B; }

private:
    G4double fB = 0.1_T;
};
