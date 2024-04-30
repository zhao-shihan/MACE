#include "MACE/PhaseI/Detector/Description/World.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::PhaseI::Detector::Description {

using namespace LiteralUnit::Length;

World::World() :
    DescriptionBase{"World"},
    fHalfXExtent{0.5_m},
    fHalfYExtent{0.5_m},
    fHalfZExtent{0.5_m} {}

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

} // namespace MACE::PhaseI::Detector::Description
