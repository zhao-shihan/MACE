#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class SpectrometerBody final : public IEntity {
public:
    SpectrometerBody() = default;
    ~SpectrometerBody() noexcept = default;
    SpectrometerBody(const SpectrometerBody&) = delete;
    SpectrometerBody& operator=(const SpectrometerBody&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
