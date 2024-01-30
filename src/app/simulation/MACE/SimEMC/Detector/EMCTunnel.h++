#pragma once

#include "MACE/Detector/Geometry/GeometryBase.h++"

namespace MACE::SimEMC::Detector {

class EMCTunnel final : public MACE::Detector::Geometry::GeometryBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::SimEMC::Detector
