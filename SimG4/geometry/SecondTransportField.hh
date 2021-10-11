#pragma once

#include "SimG4/Global.hh"

#include "SimG4/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::SecondTransportField final : public MACE::SimG4::Geometry::BaseInterface {
public:
    SecondTransportField();

    void Create(G4Material* material, const BaseInterface* mother) override;

    void SetLength(G4double val) { fLength = val; }
    void SetRadius(G4double val) { fRadius = val; }
    void SetCenterZ(G4double val) { fCenterZ = val; }
    void SetUpXPosition(G4double val) { fUpXPosition = val; }

    auto GetLength() const { return fLength; }

private:
    G4double fLength = 100 * cm;
    G4double fRadius = 10 * cm;
    G4double fCenterZ = 120 * cm;
    G4double fUpXPosition = 50 * cm;
};