#include "Geometry/Description/World.hxx"

using namespace MACE::Geometry::Description;

World& World::Instance() {
    static World instance;
    return instance;
}
