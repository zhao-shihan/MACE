#pragma once

#include "Geometry/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class ThirdTransportField final : public IEntity {
public:
    ThirdTransportField() = default;
    ~ThirdTransportField() noexcept = default;
    ThirdTransportField(const ThirdTransportField&) = delete;
    ThirdTransportField& operator=(const ThirdTransportField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
