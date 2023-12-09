#pragma once

#include "MACE/Detector/Geometry/GeometryBase.h++"

namespace MACE::Detector::Geometry::Fast {

class BeamMonitor final : public GeometryBase {
public:
    bool Enabled() const override;

private:
    auto Construct(G4bool checkOverlaps) -> void override;
};

} // namespace MACE::Detector::Geometry::Fast
