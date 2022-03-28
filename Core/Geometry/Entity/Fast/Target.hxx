#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class Target final : public IEntity {
public:
    Target() = default;
    ~Target() noexcept = default;
    Target(const Target&) = delete;
    Target& operator=(const Target&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
