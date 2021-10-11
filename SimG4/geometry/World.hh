#pragma once


#include "SimG4/Global.hh"
#include "BaseInterface.hh"

class MACE::SimG4::Geometry::World : public MACE::SimG4::Geometry::BaseInterface {
public:
    World();

    void Create(G4Material* material, const BaseInterface*);

    void SetHalfXExtent(G4double val) { fHalfXExtent = val; }
    void SetHalfYExtent(G4double val) { fHalfYExtent = val; }
    void SetHalfZExtent(G4double val) { fHalfZExtent = val; }

private:
    G4double fHalfXExtent = 3 * m;
    G4double fHalfYExtent = 1 * m;
    G4double fHalfZExtent = 4 * m;
};