#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class BeamCounter final : public IEntity {
public:
    BeamCounter() = default;
    ~BeamCounter() noexcept = default;
    BeamCounter(const BeamCounter&) = delete;
    BeamCounter& operator=(const BeamCounter&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
