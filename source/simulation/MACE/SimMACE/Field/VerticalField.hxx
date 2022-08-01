#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4UniformMagField.hh"

namespace MACE::SimMACE::Field {

class VerticalField final : public Utility::NonMoveableBase,
                            public G4UniformMagField {
public:
    VerticalField(G4double B);

    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(B, 0, 0)); }
};

} // namespace MACE::SimMACE::Field
