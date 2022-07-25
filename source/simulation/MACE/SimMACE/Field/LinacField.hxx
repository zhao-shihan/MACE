#pragma once

#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/NonCopyableBase.hxx"

#include "G4ElectroMagneticField.hh"

namespace MACE::SimMACE::Field {

class LinacField final : public Utility::NonCopyableBase,
                         public G4ElectroMagneticField {
public:
    LinacField();

    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetTransportBField(G4double B) { fBz = B; }
    void SetLinacPotential(G4double V);

private:
    G4double fBz;
    G4double fV;
    G4double fDecayZMean;
    G4double fEz;
};

} // namespace MACE::SimMACE::Field
