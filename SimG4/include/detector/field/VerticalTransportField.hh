#include "G4UniformMagField.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Field::VerticalTransportField : public G4UniformMagField {
public:
    VerticalTransportField(G4double B);
    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(B, 0, 0)); }
};