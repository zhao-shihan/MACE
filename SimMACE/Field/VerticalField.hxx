#include "G4UniformMagField.hh"

#include "SimMACE/Global.hxx"

class MACE::SimMACE::Field::VerticalField :
    public G4UniformMagField {
public:
    VerticalField(G4double B);
    ~VerticalField() noexcept = default;
    void SetFieldNorm(G4double B) { SetFieldValue(G4ThreeVector(B, 0, 0)); }
};
