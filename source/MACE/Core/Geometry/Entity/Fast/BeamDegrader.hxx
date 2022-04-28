#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class BeamDegrader final : public IEntity {
public:
    BeamDegrader() = default;
    ~BeamDegrader() noexcept = default;
    BeamDegrader(const BeamDegrader&) = delete;
    BeamDegrader& operator=(const BeamDegrader&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
