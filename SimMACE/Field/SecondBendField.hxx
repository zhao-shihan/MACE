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
    void SetBendRadius(G4double r) { fRadius = r; }
    void SetBendFieldCenter(const G4ThreeVector& center) { fXc = center.x(); fZc = center.z(); }

private:
    G4double fB = 0.1_T;

    G4double fRadius = 50_cm;
    G4double fXc = 150_cm;
    G4double fZc = 170_cm;
};
