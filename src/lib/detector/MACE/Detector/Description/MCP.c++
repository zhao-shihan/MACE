#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

MCP::MCP() :
    DescriptionSingletonBase{"MCP"},
    fDiameter{10_cm},
    fThickness{1_mm},
    fAnodeDistance{5_mm},
    fAnodeThickness{1_mm} {}

auto MCP::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fDiameter, "Diameter");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fAnodeDistance, "AnodeDistance");
    ImportValue(node, fAnodeThickness, "AnodeThickness");
}

auto MCP::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fDiameter, "Diameter");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fAnodeDistance, "AnodeDistance");
    ExportValue(node, fAnodeThickness, "AnodeThickness");
}

} // namespace MACE::Detector::Description
