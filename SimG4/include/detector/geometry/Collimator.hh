#pragma once

#include "SimG4Global.hh"

#include "detector/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::Collimator : public MACE::SimG4::Geometry::BaseInterface {
public:
    Collimator();

    void Create(G4Material* material, const BaseInterface* mother);

    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetOuterRadius(G4double val) { fOuterRadius = val; }
    void SetThickness(G4double val) { fThickness = val; }
    void SetCount(size_t count) { ResizeVolumeSetList(count); }

private:
    G4double fInnerRadius = 5 * mm;
    G4double fOuterRadius = 75 * mm;
    G4double fLength = 40 * cm;
    G4double fThickness = 1 * mm;
};