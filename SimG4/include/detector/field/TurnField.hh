#pragma once

#include "G4MagneticField.hh"

#include "SimG4Global.hh"


class MACE::SimG4::Field::TurnField : public G4MagneticField {
public:
    TurnField();
    void GetFieldValue(const G4double* x, G4double* B) const override;

    void SetTransportMagneticField(G4double B) { fB = B; }

private:
    G4double fB = 0.1 * tesla;
    G4double fXc = 30 * cm;
    G4double fZc = 140 * cm;
};
