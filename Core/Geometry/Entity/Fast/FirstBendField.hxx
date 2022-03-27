#pragma once

#include "Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class FirstBendField final : public IEntity {
public:
    FirstBendField() = default;
    ~FirstBendField() noexcept = default;
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
