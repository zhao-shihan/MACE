#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class MCP final : public IEntity {
public:
    MCP() = default;
    ~MCP() noexcept = default;
    MCP(const MCP&) = delete;
    MCP& operator=(const MCP&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
