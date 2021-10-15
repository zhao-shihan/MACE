#include "G4UniformMagField.hh"

#include "SimG4/Global.hh"

class MACE::SimG4::Field::ParallelField : public G4UniformMagField {
public:
    ParallelField(G4double B);
    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(0, 0, B)); }
};