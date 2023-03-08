#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class BeamMonitor final : public IEntity {
public:
    bool Enabled() const override;

private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
