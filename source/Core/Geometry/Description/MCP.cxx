#include "Core/Geometry/Description/MCP.hxx"
#include "Utility/LiteralUnit.hxx"

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

void MCP::ReadImpl(const YAML::Node& node) {
    fWidth = node["Width"].as<decltype(fWidth)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
}

void MCP::WriteImpl(YAML::Node& node) const {
    node["Width"] = fWidth;
    node["Thickness"] = fThickness;
}

} // namespace MACE::Core::Geometry::Description
