#pragma once

#include "SimG4/Global.hh"

#include "SimG4/Geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::FirstBendField final : public MACE::SimG4::Geometry::BaseInterface {
public:
    FirstBendField();

    void Create(G4Material* material, const BaseInterface* mother) override;

    void SetRaidus(G4double val) { fRadius = val; }
    void SetBendRadius(G4double val) { fBendRadius = val; }
    void SetXPosition(G4double val) { fXPosition = val; }
    void SetZPosition(G4double val) { fZPosition = val; }

    auto GetRadius() const { return fRadius; }

private:
    G4double fRadius = 10 * cm;
    G4double fBendRadius = 50 * cm;
    G4double fXPosition = fBendRadius;
    G4double fZPosition = 70 * cm;
};