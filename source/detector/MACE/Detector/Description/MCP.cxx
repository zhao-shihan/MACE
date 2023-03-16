#include "MACE/Detector/Description/MCP.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

MCP::MCP() :
    DescriptionSingletonBase<MCP>(__func__),
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

} // namespace MACE::Detector::Description
