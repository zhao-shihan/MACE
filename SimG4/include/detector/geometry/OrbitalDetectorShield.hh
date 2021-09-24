#pragma once

#include "SimG4Global.hh"

#include "detector/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::OrbitalDetectorShield : public MACE::SimG4::Geometry::BaseInterface {
public:
    OrbitalDetectorShield();

    void Create(G4Material* material, const BaseInterface* mother);

    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetInnerLength(G4double val) { fInnerLength = val; }
    void SetWindowRadius(G4double val) { fWindowRadius = val; }
    void SetThickness(G4double val) { fThickness = val; }
    void SetCenterX(G4double val) { fCenterX = val; }
    void SetUpZPosition(G4double val) { fUpZPosition = val; }

private:
    G4double fInnerRadius = 25 * cm;
    G4double fInnerLength = 50 * cm;
    G4double fWindowRadius = 11 * cm;
    G4double fThickness = 5 * cm;
    G4double fCenterX = 200 * cm;
    G4double fUpZPosition = 190 * cm;
};