#include "G4UniformMagField.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::VerticalField final :
    public G4UniformMagField {
    friend DetectorConstruction;
private:
    VerticalField(G4double B);
    ~VerticalField() noexcept = default;
    VerticalField(const VerticalField&) = delete;
    VerticalField& operator=(const VerticalField&) = delete;

public:
    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(B, 0, 0)); }
};
