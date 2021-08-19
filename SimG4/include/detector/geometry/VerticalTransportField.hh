#pragma once

#include "SimG4Global.hh"

#include "detector/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::VerticalTransportField : public MACE::SimG4::Geometry::BaseInterface {
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