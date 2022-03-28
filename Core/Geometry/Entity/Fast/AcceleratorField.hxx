#pragma once

#include "Core/Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class AcceleratorField final : public IEntity {
public:
    AcceleratorField() = default;
    ~AcceleratorField() noexcept = default;
    AcceleratorField(const AcceleratorField&) = delete;
    AcceleratorField& operator=(const AcceleratorField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
