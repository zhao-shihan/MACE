#pragma once

#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Field::FirstBendField : public G4MagneticField {
public:
    FirstBendField();
    void GetFieldValue(const G4double* x, G4double* B) const override;

    void SetTransportMagneticField(G4double B) { fB = B; }
    void SetBendRadius(G4double r) { fRadius = r; }
    void SetBendFieldCenter(const G4ThreeVector& center) { fXc = center.x(); fZc = center.z(); }

private:
    G4double fB = 0.1 * tesla;

    G4double fRadius = 50 * cm;
    G4double fXc = 50 * cm;
    G4double fZc = 70 * cm;
};
