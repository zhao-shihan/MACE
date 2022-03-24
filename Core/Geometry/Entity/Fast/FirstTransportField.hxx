#pragma once

#include "Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class FirstTransportField final : public IEntity {
public:
    FirstTransportField() = default;
    ~FirstTransportField() noexcept = default;
    FirstTransportField(const FirstTransportField&) = delete;
    FirstTransportField& operator=(const FirstTransportField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
