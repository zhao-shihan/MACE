#pragma once

#include "Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class Collimator final : public IEntity {
public:
    Collimator() = default;
    ~Collimator() noexcept = default;
    Collimator(const Collimator&) = delete;
    Collimator& operator=(const Collimator&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
