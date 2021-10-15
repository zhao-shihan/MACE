#pragma once

#include "SimG4/Global.hh"

#include "SimG4/Geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::FirstTransportField final : public MACE::SimG4::Geometry::BaseInterface {
public:
    FirstTransportField();

    void Create(G4Material* material, const BaseInterface* mother) override;

    void SetRaidus(G4double val) { fRadius = val; }
    void SetLength(G4double val) { fLength = val; }
    void SetUpZPosition(G4double val) { fUpZPosition = val; }

    auto GetLength() const { return fLength; }

private:
    G4double fRadius = 10 * cm;
    G4double fLength = 20 * cm;
    G4double fUpZPosition = 50 * cm;
};