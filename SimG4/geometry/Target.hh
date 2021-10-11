#pragma once

#include "SimG4/Global.hh"

#include "SimG4/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::Target : public MACE::SimG4::Geometry::BaseInterface {
public:
    Target();

    void Create(G4Material* material, const BaseInterface* mother);

    void SetWidth(G4double val) { fWidth = val; }
    void SetThickness(G4double val) { fThickness = val; }
    void SetDownZPosition(G4double val) { fDownZPosition = val; }

private:
    G4double fWidth = 50 * mm;
    G4double fThickness = 10 * mm;
    G4double fDownZPosition = -13 * cm;
};