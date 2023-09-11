#pragma once

#include "MACE/Detector/Geometry/GeometryBase.h++"

namespace MACE::Detector::Geometry::Fast {

class EMC final : public GeometryBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Detector::Geometry::Fast
