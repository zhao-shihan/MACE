#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/BaseInterface.hh"

class MACE::Geometry::OrbitalDetectorShellField : public MACE::Geometry::BaseInterface {
public:
    OrbitalDetectorShellField();

    void Make(G4Material* material, G4VPhysicalVolume* mother);
    
    void SetRadius(G4double val) { fRadius = val; }
    void SetLength(G4double val) { fLength = val; }
    void SetCenterZ(G4double val) { fCenterZ = val; }
    void SetUpXPosition(G4double val) { fUpXPosition = val; }

private:
    G4double fRadius = 23 * cm;
    G4double fLength = 45.75222 * cm;
    G4double fCenterZ = 170 * cm;
    G4double fUpXPosition = 120 * cm;
};