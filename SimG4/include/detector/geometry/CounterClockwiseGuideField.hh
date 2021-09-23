#pragma once

#include "SimG4Global.hh"

#include "detector/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::CounterClockwiseGuideField : public MACE::SimG4::Geometry::BaseInterface {
public:
    CounterClockwiseGuideField();

    void Create(G4Material* material, const BaseInterface* mother);

    void SetRaidus(G4double val) { fRadius = val; }
    void SetBendRadius(G4double val) { fBendRadius = val; }
    void SetUpZPosition(G4double val) { fUpZPosition = val; }

private:
    G4double fRadius = 10.5 * cm;
    G4double fBendRadius = 50 * cm;
    G4double fUpZPosition = 110 * cm;
};