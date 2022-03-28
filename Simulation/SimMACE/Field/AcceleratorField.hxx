#pragma once

#include "Utility/LiteralUnit.hxx"
#include "Simulation/SimMACE/Global.hxx"

#include "G4ElectroMagneticField.hh"

namespace MACE::Simulation::SimMACE::Field {

class AcceleratorField final : public G4ElectroMagneticField {
public:
    AcceleratorField();
    ~AcceleratorField() noexcept = default;
    AcceleratorField(const AcceleratorField&) = delete;
    AcceleratorField& operator=(const AcceleratorField&) = delete;

    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetTransportBField(G4double B) { fBz = B; }
    void SetAcceleratorPotential(G4double V);

private:
    G4double fBz;
    G4double fV;
    G4double fEz;
    G4double fDecayZMean;
};

} // namespace MACE::Simulation::SimMACE::Field
