#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class World final : public IEntity {
public:
    World() = default;
    ~World() noexcept = default;
    World(const World&) = delete;
    World& operator=(const World&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
