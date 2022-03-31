#include "Core/Geometry/Description/World.hxx"

using MACE::Core::Geometry::Description::World;

World& World::Instance() noexcept {
    static World instance;
    return instance;
}
