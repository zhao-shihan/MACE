#pragma once

#include "Simulation/SimMACE/Global.hxx"

#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

namespace MACE::Simulation::SimMACE::Field {

class FirstBendField final : public G4MagneticField {
public:
    FirstBendField();
    ~FirstBendField() noexcept = default;
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

    void GetFieldValue(const G4double* x, G4double* B) const override;

    void SetTransportMagneticField(G4double B) { fB = B; }

private:
    G4double fB;
};

} // namespace MACE::Simulation::SimMACE::Field
