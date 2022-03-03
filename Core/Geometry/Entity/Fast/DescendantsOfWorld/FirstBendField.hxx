#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::FirstBendField final :
    public MACE::Geometry::Interface::Entity {
public:
    FirstBendField() = default;
    ~FirstBendField() noexcept = default;
    FirstBendField(const FirstBendField&) = delete;
    FirstBendField& operator=(const FirstBendField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
