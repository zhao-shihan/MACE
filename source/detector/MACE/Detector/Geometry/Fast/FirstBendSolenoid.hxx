#pragma once

#include "MACE/Detector/GeometryBase.hxx"

namespace MACE::Detector::Geometry::Fast {

class FirstBendSolenoid final : public GeometryBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
