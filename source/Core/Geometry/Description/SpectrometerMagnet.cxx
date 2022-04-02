#include "Core/Geometry/Description/SpectrometerMagnet.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SpectrometerMagnet& SpectrometerMagnet::Instance() noexcept {
    static SpectrometerMagnet instance;
    return instance;
}

SpectrometerMagnet::SpectrometerMagnet() :
    IDescription("SpectrometerMagnet"),
    fInnerRadius(50_cm),
    fOuterRadius(70_cm),
    fLength(218_cm) {}

void SpectrometerMagnet::ReadImpl(const YAML::Node& node) {
    fInnerRadius = node["InnerRadius"].as<decltype(fInnerRadius)>();
    fOuterRadius = node["OuterRadius"].as<decltype(fOuterRadius)>();
    fLength = node["Length"].as<decltype(fLength)>();
}

void SpectrometerMagnet::WriteImpl(YAML::Node& node) const {
    node["InnerRadius"] = fInnerRadius;
    node["OuterRadius"] = fOuterRadius;
    node["Length"] = fLength;
}

} // namespace MACE::Core::Geometry::Description
