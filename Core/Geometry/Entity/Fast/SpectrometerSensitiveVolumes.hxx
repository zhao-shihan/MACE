#pragma once

#include "Core/Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class SpectrometerSensitiveVolumes final : public IEntity {
public:
    SpectrometerSensitiveVolumes() = default;
    ~SpectrometerSensitiveVolumes() noexcept = default;
    SpectrometerSensitiveVolumes(const SpectrometerSensitiveVolumes&) = delete;
    SpectrometerSensitiveVolumes& operator=(const SpectrometerSensitiveVolumes&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
