#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4UniformMagField.hh"

namespace MACE::SimMACE::Field {

class ParallelField final : public NonMoveableBase,
                            public G4UniformMagField {
public:
    ParallelField(G4double B);

    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(0, 0, B)); }
};

} // namespace MACE::SimMACE::Field
