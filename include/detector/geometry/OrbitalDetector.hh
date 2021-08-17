#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/Base.hh"

class MACE::Geometry::OrbitalDetector : public MACE::Geometry::Base {
public:
    OrbitalDetector();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetWidth(G4double val) { fWidth = val; }
    void SetThickness(G4double val) { fThickness = val; }

private:
    G4double fWidth = 10 * cm;
    G4double fThickness = 1 * cm;
};