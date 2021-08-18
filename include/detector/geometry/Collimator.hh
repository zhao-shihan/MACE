#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/BaseInterface.hh"

class MACE::Geometry::Collimator : public MACE::Geometry::BaseInterface {
public:
    Collimator();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetOuterRadius(G4double val) { fOuterRadius = val; }
    void SetThickness(G4double val) { fThickness = val; }
    void SetCount(size_t count) { ResizeVolumeSetList(count); }

private:
    G4double fInnerRadius = 5 * mm;
    G4double fOuterRadius = 75 * mm;
    G4double fLength = 40 * cm;
    G4double fThickness = 1 * mm;
};