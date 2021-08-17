#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/Base.hh"

class MACE::Geometry::VerticalTransportField : public MACE::Geometry::Base {
public:
    VerticalTransportField();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetLength(G4double val) { fLength = val; }
    void SetRadius(G4double val) { fRadius = val; }
    void SetCenterZ(G4double val) { fCenterZ = val; }
    void SetUpXPosition(G4double val) { fUpXPosition = val; }

private:
    G4double fLength = 90 * cm;
    G4double fRadius = 10.5 * cm;
    G4double fCenterZ = 170 * cm;
    G4double fUpXPosition = 30 * cm;
};