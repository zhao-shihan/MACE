#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class CDCBody final : public IEntity {
public:
    CDCBody() = default;
    ~CDCBody() noexcept = default;
    CDCBody(const CDCBody&) = delete;
    CDCBody& operator=(const CDCBody&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
