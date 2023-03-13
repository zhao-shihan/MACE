#pragma once

#include "MACE/Geometry/EntityBase.hxx"

namespace MACE::Geometry::Entity::Fast {

class CDCSenseLayer final : public EntityBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
