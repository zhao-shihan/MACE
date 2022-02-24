#pragma once

#include "G4ElectroMagneticField.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Field::AcceleratorField final :
    public G4ElectroMagneticField {
public:
    AcceleratorField();
    ~AcceleratorField() noexcept = default;
    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetTransportBField(G4double B) { fBz = B; }
    void SetAcceleratorPotential(G4double V);
    void SetAccelerateBegin(G4double beginZPos);
    void SetAccelerateEnd(G4double endZPos);

private:
    G4double fBz = 0.1_T;
    G4double fEz = 7_kV / (30_cm - 13.02_mm);

    G4double fV = 7_kV;
    G4double fAccelerateBegin = 13.02_mm;
    G4double fAccelerateEnd = 30_cm;
};
