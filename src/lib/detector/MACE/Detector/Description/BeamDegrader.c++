#include "MACE/Compatibility/std23/unreachable.h++"
#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

BeamDegrader::BeamDegrader() :
    DescriptionSingletonBase{"BeamDegrader"},
    fEnabled{true},
    fWidth{5_cm},
    fThickness{300_um},
    fDistanceToTarget{1_cm} {}

auto BeamDegrader::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fEnabled, "Enabled");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fDistanceToTarget, "DistanceToTarget");
}

auto BeamDegrader::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fEnabled, "Enabled");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fDistanceToTarget, "DistanceToTarget");
}

} // namespace MACE::Detector::Description
