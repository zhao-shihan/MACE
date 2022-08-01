#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class BeamMonitor final : public IEntity {
public:
    BeamMonitor() = default;
    ~BeamMonitor() noexcept = default;
    BeamMonitor(const BeamMonitor&) = delete;
    BeamMonitor& operator=(const BeamMonitor&) = delete;

    bool IsEnabled() const override;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
