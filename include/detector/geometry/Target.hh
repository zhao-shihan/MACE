#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/Base.hh"

class MACE::Geometry::Target : public MACE::Geometry::Base {
public:
    Target();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetWidth(G4double val) { fWidth = val; }
    void SetThickness(G4double val) { fThickness = val; }
    void SetDownZPosition(G4double val) { fDownZPosition = val; }

private:
    G4double fWidth = 50 * mm;
    G4double fThickness = 10 * mm;
    G4double fDownZPosition = -3 * cm;
};