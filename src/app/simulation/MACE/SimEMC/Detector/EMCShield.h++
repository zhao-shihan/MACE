#pragma once

#include "MACE/Detector/Geometry/GeometryBase.h++"

namespace MACE::SimEMC::Detector {

class EMCShield final : public MACE::Detector::Geometry::GeometryBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::SimEMC::Detector
