#pragma once

#include "MACE/Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class CDCSenseWire final : public IEntity {
public:
    CDCSenseWire() = default;
    ~CDCSenseWire() noexcept = default;
    CDCSenseWire(const CDCSenseWire&) = delete;
    CDCSenseWire& operator=(const CDCSenseWire&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
