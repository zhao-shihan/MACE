#pragma once

#include "MACE/Geometry/EntityBase.hxx"

namespace MACE::Geometry::Entity::Fast {

class BeamMonitor final : public EntityBase {
public:
    bool Enabled() const override;

private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
