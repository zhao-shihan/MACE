#pragma once

#include "Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class SecondBendField final : public IEntity {
public:
    SecondBendField() = default;
    ~SecondBendField() noexcept = default;
    SecondBendField(const SecondBendField&) = delete;
    SecondBendField& operator=(const SecondBendField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
