#include "MACE/Detector/Description/World.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

World::World() :
    DescriptionSingletonBase{"World"},
    fHalfXExtent{2.5_m},
    fHalfYExtent{1_m},
    fHalfZExtent{4_m} {}

auto World::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fHalfXExtent, "HalfXExtent");
    ImportValue(node, fHalfYExtent, "HalfYExtent");
    ImportValue(node, fHalfZExtent, "HalfZExtent");
}

auto World::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fHalfXExtent, "HalfXExtent");
    ExportValue(node, fHalfYExtent, "HalfYExtent");
    ExportValue(node, fHalfZExtent, "HalfZExtent");
}

} // namespace MACE::Detector::Description
