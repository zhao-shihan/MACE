#include "MACE/Core/Geometry/Description/MCP.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

MCP& MCP::Instance() noexcept {
    static MCP instance;
    return instance;
}

MCP::MCP() :
    IDescription("MCP"),
    fWidth(15_cm),
    fThickness(1_cm) {}

void MCP::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "Width", fWidth);
    ReadValueNode(node, "Thickness", fThickness);
}

void MCP::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "Width", fWidth);
    WriteValueNode(node, "Thickness", fThickness);
}

} // namespace MACE::Core::Geometry::Description
