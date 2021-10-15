#pragma once

#include "SimG4/Global.hh"

#include "SimG4/Geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::SelectorField : public MACE::SimG4::Geometry::BaseInterface {
public:
    SelectorField();

    void Create(G4Material* material, const BaseInterface* mother);

    void SetRaidus(G4double val) { fRadius = val; }
    void SetLength(G4double val) { fLength = val; }
    void SetZPosition(G4double val) { fZPosition = val; }

private:
    G4double fRadius = 10 * cm;
    G4double fLength = 30 * cm;
    G4double fZPosition = 20 * cm;
};
