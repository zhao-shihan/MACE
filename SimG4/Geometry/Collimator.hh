#pragma once

#include "SimG4/Global.hh"

#include "SimG4/Geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::Collimator final : public MACE::SimG4::Geometry::BaseInterface {
public:
    Collimator();

    void Create(G4Material* material, const BaseInterface* mother) override;

    void SetInnerRadius(G4double val) { fInnerRadius = val; }
    void SetOuterRadius(G4double val) { fOuterRadius = val; }
    void SetThickness(G4double val) { fThickness = val; }
    void SetZPosition(G4double val) { fZPosition = val; }
    void SetCount(size_t count) { ResizeVolumeSetList(count); }

private:
    G4double fInnerRadius = 5 * mm;
    G4double fOuterRadius = 75 * mm;
    G4double fLength = 30 * cm;
    G4double fZPosition = -20 * cm;
    G4double fThickness = 1 * mm;
};