#pragma once

#include "G4ElectroMagneticField.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::AcceleratorField final :
    public G4ElectroMagneticField {
    friend DetectorConstruction;
private:
    AcceleratorField();
    ~AcceleratorField() noexcept = default;
    AcceleratorField(const AcceleratorField&) = delete;
    AcceleratorField& operator=(const AcceleratorField&) = delete;

public:
    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetTransportBField(G4double B) { fBz = B; }
    void SetAcceleratorPotential(G4double V);
    void SetMuoniumDecayAvgZ(G4double decayAvgZ);

private:
    G4double fBz = 0.1_T;
    G4double fEz;

    G4double fV = 7_kV;
    G4double fMuoniumDecayAvgZ = 13.05_mm;
};
