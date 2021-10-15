#pragma once

#include "SimG4/Global.hh"

#include "SimG4/Geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::ThirdTransportField final : public MACE::SimG4::Geometry::BaseInterface {
public:
    ThirdTransportField();

    void Create(G4Material* material, const BaseInterface* mother) override;

    void SetLength(G4double val) { fLength = val; }
    void SetRadius(G4double val) { fRadius = val; }
    void SetCenterX(G4double val) { fCenterX = val; }
    void SetUpZPosition(G4double val) { fUpZPosition = val; }

    auto GetLength() const { return fLength; }

private:
    G4double fLength = 20 * cm;
    G4double fRadius = 10 * cm;
    G4double fCenterX = 200 * cm;
    G4double fUpZPosition = 170 * cm;
};