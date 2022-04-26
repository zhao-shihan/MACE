#include "MACE/Core/Geometry/Description/EMCalShield.hxx"
#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

EMCalShield& EMCalShield::Instance() noexcept {
    static EMCalShield instance;
    return instance;
}

EMCalShield::EMCalShield() :
    IDescription("EMCalShield"),
    fInnerRadius(30_cm),
    fInnerLength(80_cm),
    fWindowRadius(12.7_cm),
    fThickness(5_cm) {}

void EMCalShield::ReadImpl(const YAML::Node& node) {
    fInnerRadius = node["InnerRadius"].as<decltype(fInnerRadius)>();
    fInnerLength = node["InnerLength"].as<decltype(fInnerLength)>();
    fWindowRadius = node["WindowRadius"].as<decltype(fWindowRadius)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
}

void EMCalShield::WriteImpl(YAML::Node& node) const {
    node["InnerRadius"] = fInnerRadius;
    node["InnerLength"] = fInnerLength;
    node["WindowRadius"] = fWindowRadius;
    node["Thickness"] = fThickness;
}

} // namespace MACE::Core::Geometry::Description
