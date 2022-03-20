#include "G4UniformMagField.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::ParallelField final :
    public G4UniformMagField {
    friend DetectorConstruction;

private:
    ParallelField(G4double B);
    ~ParallelField() noexcept = default;
    ParallelField(const ParallelField&) = delete;
    ParallelField& operator=(const ParallelField&) = delete;

public:
    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(0, 0, B)); }
};
