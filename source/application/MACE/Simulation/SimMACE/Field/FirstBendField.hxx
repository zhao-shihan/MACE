#pragma once

#include "G4MagneticField.hh"
#include "G4Transform3D.hh"

namespace MACE::Simulation::SimMACE::Field {

class FirstBendField final : public G4MagneticField {
public:
    FirstBendField();
    ~FirstBendField() noexcept = default;
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

    void GetFieldValue(const G4double* x, G4double* B) const override;

    void SetTransportMagneticField(G4double B) { fB0R0 = B * fBendRadius; }

private:
    const G4Transform3D fGeomTransform;
    const G4double fBendRadius;
    G4double fB0R0;
};

} // namespace MACE::Simulation::SimMACE::Field
