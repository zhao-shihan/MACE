#pragma once

#include "MACE/Utility/LiteralUnit.hxx"

#include "G4ElectroMagneticField.hh"

namespace MACE::Simulation::SimMACE::Field {

class LinacField final : public G4ElectroMagneticField {
public:
    LinacField();
    ~LinacField() noexcept = default;
    LinacField(const LinacField&) = delete;
    LinacField& operator=(const LinacField&) = delete;

    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetTransportBField(G4double B) { fBz = B; }
    void SetLinacPotential(G4double V);

private:
    G4double fBz;
    G4double fV;
    G4double fDecayZMean;
    G4double fEz;
};

} // namespace MACE::Simulation::SimMACE::Field
