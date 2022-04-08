#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class CDCSensitiveVolume final : public IEntity {
public:
    CDCSensitiveVolume() = default;
    ~CDCSensitiveVolume() noexcept = default;
    CDCSensitiveVolume(const CDCSensitiveVolume&) = delete;
    CDCSensitiveVolume& operator=(const CDCSensitiveVolume&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
