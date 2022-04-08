#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class EMCalShield final : public IEntity {
public:
    EMCalShield() = default;
    ~EMCalShield() noexcept = default;
    EMCalShield(const EMCalShield&) = delete;
    EMCalShield& operator=(const EMCalShield&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
