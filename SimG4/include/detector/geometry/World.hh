#pragma once


#include "SimG4Global.hh"
#include "BaseInterface.hh"

class MACE::SimG4::Geometry::World : public MACE::SimG4::Geometry::BaseInterface {
public:
    World();

    void Make(G4Material* material, G4VPhysicalVolume*);

    void SetHalfXExtent(G4double val) { fHalfXExtent = val; }
    void SetHalfYExtent(G4double val) { fHalfYExtent = val; }
    void SetHalfZExtent(G4double val) { fHalfZExtent = val; }

private:
    G4double fHalfXExtent = 3 * m;
    G4double fHalfYExtent = 1 * m;
    G4double fHalfZExtent = 3 * m;
};