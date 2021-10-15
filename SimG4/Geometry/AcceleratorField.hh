#pragma once

#include "SimG4/Global.hh"

#include "SimG4/Geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::AcceleratorField : public MACE::SimG4::Geometry::BaseInterface {
public:
    AcceleratorField();

    void Create(G4Material* material, const BaseInterface* mother);

    void SetWidth(G4double val) { fWidth = val; }
    void SetUpStreamLength(G4double val) { fUpStreamLength = val; }
    void SetDownStreamLength(G4double val) { fDownStreamLength = val; }

private:
    G4double fWidth = 7 * M_SQRT2 * cm;
    G4double fUpStreamLength = 4 * cm;
    G4double fDownStreamLength = 30 * cm;
};
