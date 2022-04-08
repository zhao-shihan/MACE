#include "MACE/Core/Geometry/Description/World.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

World& World::Instance() noexcept {
    static World instance;
    return instance;
}

World::World() :
    IDescription("World"),
    fHalfXExtent(3_m),
    fHalfYExtent(1_m),
    fHalfZExtent(4_m) {}

void World::ReadImpl(const YAML::Node& node) {
    fHalfXExtent = node["HalfXExtent"].as<decltype(fHalfXExtent)>();
    fHalfYExtent = node["HalfYExtent"].as<decltype(fHalfYExtent)>();
    fHalfZExtent = node["HalfZExtent"].as<decltype(fHalfZExtent)>();
}

void World::WriteImpl(YAML::Node& node) const {
    node["HalfXExtent"] = fHalfXExtent;
    node["HalfYExtent"] = fHalfYExtent;
    node["HalfZExtent"] = fHalfZExtent;
}

} // namespace MACE::Core::Geometry::Description
