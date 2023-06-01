#include "MACE/Detector/Description/World.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

World::World() :
    DescriptionSingletonBase<World>(__func__),
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

} // namespace MACE::Detector::Description
