#pragma once

#include "Geometry/Interface/Entity.hxx"

class MACE::Geometry::Entity::Fast::World final :
    public MACE::Geometry::Interface::Entity {
public:
    World() = default;
    ~World() noexcept = default;
    World(const World&) = delete;
    World& operator=(const World&) = delete;

private:
    void ConstructSelf(G4bool checkOverlaps) override;
};
