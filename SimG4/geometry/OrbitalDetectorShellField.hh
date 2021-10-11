#pragma once

#include "SimG4/Global.hh"

#include "SimG4/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::OrbitalDetectorShellField : public MACE::SimG4::Geometry::BaseInterface {
public:
    OrbitalDetectorShellField();

    void Create(G4Material* material, const BaseInterface* mother) override;
    
    void SetRadius(G4double val) { fRadius = val; }
    void SetLength(G4double val) { fLength = val; }
    void SetCenterX(G4double val) { fCenterX = val; }
    void SetUpZPosition(G4double val) { fUpZPosition = val; }

    auto GetLength() const { return fLength; }

private:
    G4double fRadius = 23 * cm;
    G4double fLength = 50 * cm;
    G4double fCenterX = 200 * cm;
    G4double fUpZPosition = 190 * cm;
};