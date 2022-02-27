#include "G4UniformMagField.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::ParallelField final :
    public G4UniformMagField {
public:
    ParallelField(G4double B);
    ~ParallelField() noexcept = default;

    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(0, 0, B)); }
};
