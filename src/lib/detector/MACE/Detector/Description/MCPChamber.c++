#include "MACE/Detector/Description/MCPChamber.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

MCPChamber::MCPChamber() :
    DescriptionSingletonBase{"MCPChamber"},
    fInnerRadius{10_cm},
    fThickness{500_um} {}

auto MCPChamber::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fThickness, "Thickness");
}

auto MCPChamber::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Detector::Description
