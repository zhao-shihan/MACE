#include "MACE/Core/Geometry/Description/World.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

World::World() :
    ISingletonDescription<World>(__func__),
    fHalfXExtent(3_m),
    fHalfYExtent(1_m),
    fHalfZExtent(4_m) {}

void World::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "HalfXExtent", fHalfXExtent);
    ReadValueNode(node, "HalfYExtent", fHalfYExtent);
    ReadValueNode(node, "HalfZExtent", fHalfZExtent);
}

void World::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "HalfXExtent", fHalfXExtent);
    WriteValueNode(node, "HalfYExtent", fHalfYExtent);
    WriteValueNode(node, "HalfZExtent", fHalfZExtent);
}

} // namespace MACE::Core::Geometry::Description
