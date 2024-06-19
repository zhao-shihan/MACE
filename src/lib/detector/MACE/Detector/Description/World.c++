#include "MACE/Detector/Description/World.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

World::World() :
    DescriptionBase{"World"},
    fHalfXExtent{3_m},
    fHalfYExtent{1_m},
    fHalfZExtent{4_m} {}

auto World::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fHalfXExtent, "HalfXExtent");
    ImportValue(node, fHalfYExtent, "HalfYExtent");
    ImportValue(node, fHalfZExtent, "HalfZExtent");
}

auto World::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fHalfXExtent, "HalfXExtent");
    ExportValue(node, fHalfYExtent, "HalfYExtent");
    ExportValue(node, fHalfZExtent, "HalfZExtent");
}

} // namespace MACE::Detector::Description
