#pragma once

#include "Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class SpectrometerSenseWires final : public IEntity {
public:
    SpectrometerSenseWires() = default;
    ~SpectrometerSenseWires() noexcept = default;
    SpectrometerSenseWires(const SpectrometerSenseWires&) = delete;
    SpectrometerSenseWires& operator=(const SpectrometerSenseWires&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
