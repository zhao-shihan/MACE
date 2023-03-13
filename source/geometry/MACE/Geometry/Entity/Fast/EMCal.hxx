#pragma once

#include "MACE/Geometry/EntityBase.hxx"

namespace MACE::Geometry::Entity::Fast {

class EMCal final : public EntityBase {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
