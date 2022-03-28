#include "Core/Geometry/Description/World.hxx"

using MACE::Geometry::Description::World;

World& World::Instance() noexcept {
    static World instance;
    return instance;
}
