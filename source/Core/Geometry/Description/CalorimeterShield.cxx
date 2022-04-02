#include "Core/Geometry/Description/CalorimeterShield.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

CalorimeterShield& CalorimeterShield::Instance() noexcept {
    static CalorimeterShield instance;
    return instance;
}

CalorimeterShield::CalorimeterShield() :
    IDescription("CalorimeterShield"),
    fInnerRadius(30_cm),
    fInnerLength(80_cm),
    fWindowRadius(12.7_cm),
    fThickness(5_cm) {}

void CalorimeterShield::ReadImpl(const YAML::Node& node) {
    fInnerRadius = node["InnerRadius"].as<decltype(fInnerRadius)>();
    fInnerLength = node["InnerLength"].as<decltype(fInnerLength)>();
    fWindowRadius = node["WindowRadius"].as<decltype(fWindowRadius)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
}

void CalorimeterShield::WriteImpl(YAML::Node& node) const {
    node["InnerRadius"] = fInnerRadius;
    node["InnerLength"] = fInnerLength;
    node["WindowRadius"] = fWindowRadius;
    node["Thickness"] = fThickness;
}

} // namespace MACE::Core::Geometry::Description
