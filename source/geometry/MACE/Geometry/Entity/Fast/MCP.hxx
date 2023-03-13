#pragma once

#include "MACE/Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class MCP final : public IEntity {
private:
    void Construct(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
