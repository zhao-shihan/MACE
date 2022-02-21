#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::AcceleratorField final :
    public MACE::Geometry::Interface::Entity {
public:
    AcceleratorField() = default;
    ~AcceleratorField() noexcept = default;
    AcceleratorField(const AcceleratorField&) = delete;
    AcceleratorField& operator=(const AcceleratorField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
