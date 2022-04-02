#include "Core/Geometry/Description/SpectrometerShield.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SpectrometerShield& SpectrometerShield::Instance() noexcept {
    static SpectrometerShield instance;
    return instance;
}

SpectrometerShield::SpectrometerShield() :
    IDescription("SpectrometerShield"),
    fInnerRadius(72_cm),
    fInnerLength(222_cm),
    fWindowRadius(12.7_cm),
    fThickness(5_cm) {}

void SpectrometerShield::ReadImpl(const YAML::Node& node) {
    fInnerRadius = node["InnerRadius"].as<decltype(fInnerRadius)>();
    fInnerLength = node["InnerLength"].as<decltype(fInnerLength)>();
    fWindowRadius = node["WindowRadius"].as<decltype(fWindowRadius)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
}

void SpectrometerShield::WriteImpl(YAML::Node& node) const {
    node["InnerRadius"] = fInnerRadius;
    node["InnerLength"] = fInnerLength;
    node["WindowRadius"] = fWindowRadius;
    node["Thickness"] = fThickness;
}

} // namespace MACE::Core::Geometry::Description
