#pragma once

#include "Simulation/SimMACE/Global.hxx"

#include "G4UniformMagField.hh"

namespace MACE::Simulation::SimMACE::Field {

class ParallelField final : public G4UniformMagField {
public:
    ParallelField(G4double B);
    ~ParallelField() noexcept = default;
    ParallelField(const ParallelField&) = delete;
    ParallelField& operator=(const ParallelField&) = delete;

    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(0, 0, B)); }
};

} // namespace MACE::Simulation::SimMACE::Field
