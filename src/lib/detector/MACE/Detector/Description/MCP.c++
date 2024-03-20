#include "MACE/Detector/Description/MCP.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Time;
using namespace LiteralUnit::Length;

MCP::MCP() :
    DescriptionSingletonBase{"MCP"},
    // Geometry
    fDiameter{10_cm},
    fThickness{1_mm},
    fAnodeDistance{5_mm},
    fAnodeThickness{1_mm},
    // Detection
    fTimeResolutionFWHM{1_ns} {}

auto MCP::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fDiameter, "Diameter");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fAnodeDistance, "AnodeDistance");
    ImportValue(node, fAnodeThickness, "AnodeThickness");
    // Detection
    ImportValue(node, fTimeResolutionFWHM, "TimeResolutionFWHM");
}

auto MCP::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fDiameter, "Diameter");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fAnodeDistance, "AnodeDistance");
    ExportValue(node, fAnodeThickness, "AnodeThickness");
    // Detection
    ExportValue(node, fTimeResolutionFWHM, "TimeResolutionFWHM");
}

} // namespace MACE::Detector::Description
