#include "G4UniformMagField.hh"

#include "SimG4/Global.hxx"

class MACE::SimG4::Field::VerticalField : public G4UniformMagField {
public:
    VerticalField(G4double B);
    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(B, 0, 0)); }
};