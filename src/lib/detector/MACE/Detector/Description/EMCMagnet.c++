#include "MACE/Detector/Description/EMCMagnet.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

EMCMagnet::EMCMagnet() :
    DescriptionSingletonBase<EMCMagnet>{"EMCMagnet"},
    fInnerRadius{50_cm},
    fOuterRadius{55_cm},
    fLength{95_cm} {}

auto EMCMagnet::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fLength, "Length");
}

auto EMCMagnet::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fLength, "Length");
}

} // namespace MACE::Detector::Description
