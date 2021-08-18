#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/BaseInterface.hh"

class MACE::Geometry::Calorimeter : public MACE::Geometry::BaseInterface {
public:
    Calorimeter();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetOuterRadius(G4double val) { fOuterRadius = val; }
    void SetLength(G4double val) { fLength = val; }

private:
    G4double fInnerRadius = 8.5 * cm;
    G4double fOuterRadius = 14.5 * cm;
    G4double fLength = 28 * cm;
};