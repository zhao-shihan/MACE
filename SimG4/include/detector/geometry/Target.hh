#pragma once

#include "SimG4Global.hh"

#include "detector/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::Target : public MACE::SimG4::Geometry::BaseInterface {
public:
    Target();

    void Create(G4Material* material, G4VPhysicalVolume* mother);

    void SetWidth(G4double val) { fWidth = val; }
    void SetThickness(G4double val) { fThickness = val; }
    void SetDownZPosition(G4double val) { fDownZPosition = val; }

private:
    G4double fWidth = 50 * mm;
    G4double fThickness = 10 * mm;
    G4double fDownZPosition = -13 * cm;
};