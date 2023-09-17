#pragma once

#include "MACE/Detector/Geometry/GeometryBase.h++"

namespace MACE::Detector::Geometry::Fast {

class BeamMonitor final : public GeometryBase {
public:
    bool Enabled() const override;

private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Detector::Geometry::Fast
