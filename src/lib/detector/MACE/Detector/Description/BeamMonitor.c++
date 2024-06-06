#include "MACE/Detector/Description/BeamMonitor.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "muc/utility"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

BeamMonitor::BeamMonitor() :
    DescriptionBase{"BeamMonitor"},
    fEnabled{false},
    fWidth{4_cm},
    fThickness{500_um},
    fDistanceToTarget{5_mm} {}

auto BeamMonitor::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fEnabled, "Enabled");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fDistanceToTarget, "DistanceToTarget");
}

auto BeamMonitor::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fEnabled, "Enabled");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fDistanceToTarget, "DistanceToTarget");
}

} // namespace MACE::Detector::Description
