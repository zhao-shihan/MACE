#pragma once

#include "SimG4Global.hh"

#include "detector/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::TurnField : public MACE::SimG4::Geometry::BaseInterface {
public:
    TurnField();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetHalfHeight(G4double val) { fHalfHeight = val; }
    void SetWidth(G4double val) { fWidth = val; }
    void SetUpZPosition(G4double val) { fUpZPosition = val; }
    
private:
    G4double fHalfHeight = 11 * cm;
    G4double fWidth = 60 * cm;
    G4double fUpZPosition = 140 * cm;
};