#pragma once

#include "MACEGlobal.hh"
#include "detector/geometry/BaseInterface.hh"

class MACE::Geometry::OrbitalDetectorShield : public MACE::Geometry::BaseInterface {
public:
    OrbitalDetectorShield();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetInnerLength(G4double val) { fInnerLength = val; }
    void SetWindowRadius(G4double val) { fWindowRadius = val; }
    void SetThickness(G4double val) { fThickness = val; }
    void SetCenterZ(G4double val) { fCenterZ = val; }
    void SetUpXPosition(G4double val) { fUpXPosition = val; }

private:
    G4double fInnerRadius = 25 * cm;
    G4double fInnerLength = 50 * cm;
    G4double fWindowRadius = 11 * cm;
    G4double fThickness = 5 * cm;
    G4double fCenterZ = 170 * cm;
    G4double fUpXPosition = 120 * cm;
};