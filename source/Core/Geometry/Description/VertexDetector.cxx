#include "Core/Geometry/Description/VertexDetector.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

VertexDetector& VertexDetector::Instance() noexcept {
    static VertexDetector instance;
    return instance;
}

VertexDetector::VertexDetector() :
    IDescription("VertexDetector"),
    fWidth(15_cm),
    fThickness(1_cm) {}

void VertexDetector::ReadImpl(const YAML::Node& node) {
    fWidth = node["Width"].as<decltype(fWidth)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
}

void VertexDetector::WriteImpl(YAML::Node& node) const {
    node["Width"] = fWidth;
    node["Thickness"] = fThickness;
}

} // namespace MACE::Core::Geometry::Description
