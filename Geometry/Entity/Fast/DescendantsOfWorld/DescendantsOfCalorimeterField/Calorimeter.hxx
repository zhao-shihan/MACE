#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::Calorimeter final :
    public MACE::Geometry::Interface::Entity {
public:
    Calorimeter() = default;
    ~Calorimeter() noexcept = default;
    Calorimeter(const Calorimeter&) = delete;
    Calorimeter& operator=(const Calorimeter&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
