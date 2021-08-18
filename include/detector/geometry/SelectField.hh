#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/BaseInterface.hh"

class MACE::Geometry::SelectField : public MACE::Geometry::BaseInterface {
public:
    SelectField();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetRaidus(G4double val) { fRadius = val; }
    void SetLength(G4double val) { fLength = val; }

private:
    G4double fRadius = 10.5 * cm;
    G4double fLength = 30 * cm;
};
