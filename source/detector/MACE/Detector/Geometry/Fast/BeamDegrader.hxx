#pragma once

#include "MACE/Detector/Geometry/GeometryBase.hxx"

namespace MACE::Detector::Geometry::Fast {

class BeamDegrader final : public GeometryBase {
public:
    bool Enabled() const override;

private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Detector::Geometry::Fast
