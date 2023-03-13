#include "MACE/Geometry/Description/World.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Geometry::Description {

using namespace LiteralUnit::Length;

World::World() :
    ISingletonDescription<World>(__func__),
    fHalfXExtent(3_m),
    fHalfYExtent(1_m),
    fHalfZExtent(4_m) {}

void World::ImportValues(const YAML::Node& node) {
    ImportValue(node, fHalfXExtent, "HalfXExtent");
    ImportValue(node, fHalfYExtent, "HalfYExtent");
    ImportValue(node, fHalfZExtent, "HalfZExtent");
}

void World::ExportValues(YAML::Node& node) const {
    ExportValue(node, fHalfXExtent, "HalfXExtent");
    ExportValue(node, fHalfYExtent, "HalfYExtent");
    ExportValue(node, fHalfZExtent, "HalfZExtent");
}

} // namespace MACE::Geometry::Description
