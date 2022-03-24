#pragma once

#include "Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class World final : public IEntity {
public:
    World() = default;
    ~World() noexcept = default;
    World(const World&) = delete;
    World& operator=(const World&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
