#pragma once

#include "MACE/Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class BeamMonitor final : public IEntity {
public:
    bool Enabled() const override;

private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
