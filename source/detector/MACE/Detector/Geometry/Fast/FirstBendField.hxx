#pragma once

#include "MACE/Detector/GeometryBase.hxx"

namespace MACE::Detector::Geometry::Fast {

class FirstBendField final : public GeometryBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
