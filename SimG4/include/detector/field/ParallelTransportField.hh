#include "G4UniformMagField.hh"

#include "SimG4Global.hh"

class MACE::SimG4::Field::ParallelTransportField : public G4UniformMagField {
public:
    ParallelTransportField(G4double B);
    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(0, 0, B)); }
};