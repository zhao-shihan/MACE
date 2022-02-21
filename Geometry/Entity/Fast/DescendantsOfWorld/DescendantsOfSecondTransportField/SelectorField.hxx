#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::SelectorField final :
    public MACE::Geometry::Interface::Entity {
public:
    SelectorField() = default;
    ~SelectorField() noexcept = default;
    SelectorField(const SelectorField&) = delete;
    SelectorField& operator=(const SelectorField&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
