#pragma once

#include "SimG4Global.hh"

#include "detector/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::OrbitalDetectorShellField : public MACE::SimG4::Geometry::BaseInterface {
public:
    OrbitalDetectorShellField();

    void Create(G4Material* material, G4VPhysicalVolume* mother);
    
    void SetRadius(G4double val) { fRadius = val; }
    void SetLength(G4double val) { fLength = val; }
    void SetCenterZ(G4double val) { fCenterZ = val; }
    void SetUpXPosition(G4double val) { fUpXPosition = val; }

private:
    G4double fRadius = 23 * cm;
    G4double fLength = 45.75222 * cm;
    G4double fCenterZ = 160 * cm;
    G4double fUpXPosition = 140 * cm;
};