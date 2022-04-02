#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Core::Geometry::Entity::Fast {

class CDCFieldWire final : public IEntity {
public:
    CDCFieldWire() = default;
    ~CDCFieldWire() noexcept = default;
    CDCFieldWire(const CDCFieldWire&) = delete;
    CDCFieldWire& operator=(const CDCFieldWire&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Core::Geometry::Entity::Fast
