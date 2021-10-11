#pragma once

#include "SimG4/Global.hh"

#include "SimG4/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::OrbitalDetector : public MACE::SimG4::Geometry::BaseInterface {
public:
    OrbitalDetector();

    void Create(G4Material* material, const BaseInterface* mother);

    void SetWidth(G4double val) { fWidth = val; }
    void SetThickness(G4double val) { fThickness = val; }

private:
    G4double fWidth = 10 * cm;
    G4double fThickness = 1 * cm;
};