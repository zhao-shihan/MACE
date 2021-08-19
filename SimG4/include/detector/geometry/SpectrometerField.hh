#pragma once

#include "SimG4Global.hh"

#include "BaseInterface.hh"

class MACE::SimG4::Geometry::SpectrometerField : public MACE::SimG4::Geometry::BaseInterface {
public:
    SpectrometerField();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetRadius(G4double val) { fRadius = val; }
    void SetLength(G4double val) { fLength = val; }

private:
    G4double fRadius = 37 * cm;
    G4double fLength = 100 * cm;
};
