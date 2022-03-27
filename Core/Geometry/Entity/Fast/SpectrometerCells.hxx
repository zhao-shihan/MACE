#pragma once

#include "Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class SpectrometerCells final : public IEntity {
public:
    SpectrometerCells() = default;
    ~SpectrometerCells() noexcept = default;
    SpectrometerCells(const SpectrometerCells&) = delete;
    SpectrometerCells& operator=(const SpectrometerCells&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
