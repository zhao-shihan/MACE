#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class EMCalField final : public IEntity {
public:
    EMCalField() = default;
    ~EMCalField() noexcept = default;
    EMCalField(const EMCalField&) = delete;
    EMCalField& operator=(const EMCalField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
