#pragma once

#include "Core/Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class SpectrometerReadoutLayers final : public IEntity {
public:
    SpectrometerReadoutLayers() = default;
    ~SpectrometerReadoutLayers() noexcept = default;
    SpectrometerReadoutLayers(const SpectrometerReadoutLayers&) = delete;
    SpectrometerReadoutLayers& operator=(const SpectrometerReadoutLayers&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
