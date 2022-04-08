#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class SpectrometerMagnet final : public IEntity {
public:
    SpectrometerMagnet() = default;
    ~SpectrometerMagnet() noexcept = default;
    SpectrometerMagnet(const SpectrometerMagnet&) = delete;
    SpectrometerMagnet& operator=(const SpectrometerMagnet&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
