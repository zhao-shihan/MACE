#pragma once

#include "MACE/Detector/Geometry/GeometryBase.h++"

namespace MACE::Detector::Geometry::Fast {

class Filter final : public GeometryBase {
private:
    auto Construct(G4bool checkOverlaps) -> void override;
};

} // namespace MACE::Detector::Geometry::Fast
