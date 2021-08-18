#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/BaseInterface.hh"

class MACE::Geometry::AcceleratorField : public MACE::Geometry::BaseInterface {
public:
    AcceleratorField();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetWidth(G4double val) { fWidth = val; }
    void SetUpStreamLength(G4double val) { fUpStreamLength = val; }
    void SetDownStreamLength(G4double val) { fDownStreamLength = val; }

private:
    G4double fWidth = 7 * M_SQRT2 * cm;
    G4double fUpStreamLength = 4 * cm;
    G4double fDownStreamLength = 10 * cm;
};
