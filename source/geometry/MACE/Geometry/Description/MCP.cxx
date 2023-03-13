#include "MACE/Geometry/Description/MCP.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Geometry::Description {

using namespace LiteralUnit::Length;

MCP::MCP() :
    ISingletonDescription<MCP>(__func__),
    fWidth(15_cm),
    fThickness(1_cm) {}

void MCP::ImportValues(const YAML::Node& node) {
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
}

void MCP::ExportValues(YAML::Node& node) const {
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
}

} // namespace MACE::Geometry::Description
