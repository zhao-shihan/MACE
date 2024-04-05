#include "MACE/Detector/Description/MCPChamber.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

MCPChamber::MCPChamber() :
    DescriptionBase{"MCPChamber"},
    fInnerRadius{10_cm},
    fThickness{500_um} {}

auto MCPChamber::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fThickness, "Thickness");
}

auto MCPChamber::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Detector::Description
