#include "Geometry/Description/World.hxx"

using namespace MACE::Geometry::Description;

World& World::Instance() noexcept {
    static World instance;
    return instance;
}
