#pragma once

#include "MACE/Utility/NonMoveableBase.hxx"

#include "G4ElectroMagneticField.hh"

namespace MACE::SimMACE::Field {

class SelectorField final : public NonMoveableBase,
                            public G4ElectroMagneticField {
public:
    SelectorField();

    void GetFieldValue(const G4double*, G4double* F) const override;
    G4bool DoesFieldChangeEnergy() const override { return true; }

    void SetTransportField(G4double B) { fBTransport = B; }
    void SetSelectorElectricField(G4double E);
    void SetSelectEnergy(G4double Ek);

private:
    G4double fBTransport;
    G4double fSelectEk;
    G4double fESelect;
    G4double fBSelect;
};

} // namespace MACE::SimMACE::Field
