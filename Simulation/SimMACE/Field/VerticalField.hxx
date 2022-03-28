#pragma once

#include "Simulation/SimMACE/Global.hxx"

#include "G4UniformMagField.hh"

namespace MACE::Simulation::SimMACE::Field {

class VerticalField final : public G4UniformMagField {
public:
    VerticalField(G4double B);
    ~VerticalField() noexcept = default;
    VerticalField(const VerticalField&) = delete;
    VerticalField& operator=(const VerticalField&) = delete;

    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(B, 0, 0)); }
};

} // namespace MACE::Simulation::SimMACE::Field
