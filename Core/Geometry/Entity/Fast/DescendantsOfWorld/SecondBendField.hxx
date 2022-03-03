#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SecondBendField final :
    public MACE::Geometry::Interface::Entity {
public:
    SecondBendField() = default;
    ~SecondBendField() noexcept = default;
    SecondBendField(const SecondBendField&) = delete;
    SecondBendField& operator=(const SecondBendField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
