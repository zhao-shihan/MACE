#pragma once

#include "SimG4Global.hh"

#include "detector/geometry/BaseInterface.hh"

class MACE::SimG4::Geometry::ParallelTransportField : public MACE::SimG4::Geometry::BaseInterface {
public:
    ParallelTransportField();

    void Make(G4Material* material, G4VPhysicalVolume* mother);

    void SetRaidus(G4double val) { fRadius = val; }
    void SetLength(G4double val) { fLength = val; }
    void SetUpZPosition(G4double val) { fUpZPosition = val; }

private:
    G4double fRadius = 10.5 * cm;
    G4double fLength = 90 * cm;
    G4double fUpZPosition = 50 * cm;
};