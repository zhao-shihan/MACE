#pragma once

#include "SimG4/Global.hh"

#include "SimG4/Geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::SpectrometerShield final :
    public MACE::SimG4::Geometry::BaseInterface {
public:
    SpectrometerShield();

    void Create(G4Material* material, const BaseInterface* mother);

    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetInnerLength(G4double val) { fInnerLength = val; }
    void SetWindowRadius(G4double val) { fWindowRadius = val; }
    void SetThickness(G4double val) { fThickness = val; }

private:
    G4double fInnerRadius = 50 * cm;
    G4double fInnerLength = 110 * cm;
    G4double fWindowRadius = 11 * cm;
    G4double fThickness = 5 * cm;
};