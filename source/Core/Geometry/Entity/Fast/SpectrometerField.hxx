#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class SpectrometerField final : public IEntity {
public:
    SpectrometerField() = default;
    ~SpectrometerField() noexcept = default;
    SpectrometerField(const SpectrometerField&) = delete;
    SpectrometerField& operator=(const SpectrometerField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
