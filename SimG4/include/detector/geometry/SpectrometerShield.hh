#pragma once

#include "SimG4Global.hh"

#include "detector/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::SpectrometerShield : public MACE::SimG4::Geometry::BaseInterface {
public:
    SpectrometerShield();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetInnerLength(G4double val) { fInnerLength = val; }
    void SetWindowRadius(G4double val) { fWindowRadius = val; }
    void SetThickness(G4double val) { fThickness = val; }

private:
    G4double fInnerRadius = 50 * cm;
    G4double fInnerLength = 100 * cm;
    G4double fWindowRadius = 11 * cm;
    G4double fThickness = 5 * cm;
};