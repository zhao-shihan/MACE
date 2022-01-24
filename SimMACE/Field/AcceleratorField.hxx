#pragma once

#include "G4ElectroMagneticField.hh"

#include "SimMACE/Global.hxx"


class MACE::SimMACE::Field::AcceleratorField : public G4ElectroMagneticField {
public:
    AcceleratorField();
    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetTransportBField(G4double B) { fBz = B; }
    void SetAcceleratorPotential(G4double V);
    void SetAccelerateBegin(G4double beginZPos);
    void SetAccelerateEnd(G4double endZPos);

private:
    G4double fBz = 0.1 * tesla;
    G4double fEz = 7 * kilovolt / (30 * cm - 13.02 * mm);
    
    G4double fV = 7 * kilovolt;
    G4double fAccelerateBegin = 13.02 * mm;
    G4double fAccelerateEnd = 30 * cm;
};
