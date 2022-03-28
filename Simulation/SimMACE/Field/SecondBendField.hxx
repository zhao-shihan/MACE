#pragma once

#include "Utility/LiteralUnit.hxx"
#include "Simulation/SimMACE/Global.hxx"

#include "G4MagneticField.hh"
#include "G4ThreeVector.hh"

namespace MACE::Simulation::SimMACE::Field {

class SecondBendField final : public G4MagneticField {
public:
    SecondBendField();
    ~SecondBendField() noexcept = default;
    SecondBendField(const SecondBendField&) = delete;
    SecondBendField& operator=(const SecondBendField&) = delete;

    void GetFieldValue(const G4double* x, G4double* B) const override;

    void SetTransportMagneticField(G4double B) { fB = B; }

private:
    G4double fB;
};

} // namespace MACE::Simulation::SimMACE::Field
