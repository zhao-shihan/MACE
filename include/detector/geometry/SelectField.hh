#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/Base.hh"

class MACE::Geometry::SelectField : public MACE::Geometry::Base {
public:
    SelectField();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetWidth(G4double val) { fWidth = val; }
    void SetLength(G4double val) { fLength = val; }

private:
    G4double fWidth = 7 * M_SQRT2 * cm;
    G4double fLength = 30 * cm;
};
