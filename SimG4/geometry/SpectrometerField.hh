#pragma once

#include "SimG4/Global.hh"

#include "BaseInterface.hh"

class MACE::SimG4::Geometry::SpectrometerField : public MACE::SimG4::Geometry::BaseInterface {
public:
    SpectrometerField();

    void Create(G4Material* material, const BaseInterface* mother);

    void SetRadius(G4double val) { fRadius = val; }
    void SetLength(G4double val) { fLength = val; }

    auto GetLength() const { return fLength; }

private:
    G4double fRadius = 37 * cm;
    G4double fLength = 100 * cm;
};
