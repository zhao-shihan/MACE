#pragma once

#include "Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class SpectrometerFieldWires final : public IEntity {
public:
    SpectrometerFieldWires() = default;
    ~SpectrometerFieldWires() noexcept = default;
    SpectrometerFieldWires(const SpectrometerFieldWires&) = delete;
    SpectrometerFieldWires& operator=(const SpectrometerFieldWires&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
