#pragma once

#include "Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class SecondTransportField final : public IEntity {
public:
    SecondTransportField() = default;
    ~SecondTransportField() noexcept = default;
    SecondTransportField(const SecondTransportField&) = delete;
    SecondTransportField& operator=(const SecondTransportField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
