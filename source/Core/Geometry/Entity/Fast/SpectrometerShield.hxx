#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class SpectrometerShield final : public IEntity {
public:
    SpectrometerShield() = default;
    ~SpectrometerShield() noexcept = default;
    SpectrometerShield(const SpectrometerShield&) = delete;
    SpectrometerShield& operator=(const SpectrometerShield&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
