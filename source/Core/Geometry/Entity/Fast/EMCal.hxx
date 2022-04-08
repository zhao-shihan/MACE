#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class EMCal final : public IEntity {
public:
    EMCal() = default;
    ~EMCal() noexcept = default;
    EMCal(const EMCal&) = delete;
    EMCal& operator=(const EMCal&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
