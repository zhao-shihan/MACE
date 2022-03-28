#pragma once

#include "Core/Geometry/Entity/IEntity.hxx"

namespace MACE::Geometry::Entity::Fast {

class Calorimeter final : public IEntity {
public:
    Calorimeter() = default;
    ~Calorimeter() noexcept = default;
    Calorimeter(const Calorimeter&) = delete;
    Calorimeter& operator=(const Calorimeter&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};

} // namespace MACE::Geometry::Entity::Fast
