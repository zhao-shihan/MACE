#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

MCP::MCP() :
    DescriptionSingletonBase{"MCP"},
    fDiameter{10_cm},
    fThickness{1_cm} {}

auto MCP::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fDiameter, "Diameter");
    ImportValue(node, fThickness, "Thickness");
}

auto MCP::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fDiameter, "Diameter");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Detector::Description
