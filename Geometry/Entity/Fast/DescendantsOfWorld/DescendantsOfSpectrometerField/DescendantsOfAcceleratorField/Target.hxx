#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::Target final :
    public MACE::Geometry::Interface::Entity {
public:
    Target() = default;
    ~Target() noexcept = default;
    Target(const Target&) = delete;
    Target& operator=(const Target&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
