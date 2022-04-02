#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class CDCLayer final : public IEntity {
public:
    CDCLayer() = default;
    ~CDCLayer() noexcept = default;
    CDCLayer(const CDCLayer&) = delete;
    CDCLayer& operator=(const CDCLayer&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
