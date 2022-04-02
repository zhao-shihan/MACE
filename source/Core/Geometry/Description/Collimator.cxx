#include "Core/Geometry/Description/Collimator.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Collimator& Collimator::Instance() noexcept {
    static Collimator instance;
    return instance;
}

Collimator::Collimator() :
    IDescription("Collimator"),
    fInnerRadius(5_mm),
    fOuterRadius(65_mm),
    fLength(30_cm),
    fZPosition(-20_cm),
    fThickness(0.75_mm),
    fCount(7) {}

void Collimator::ReadImpl(const YAML::Node& node) {
    fInnerRadius = node["InnerRadius"].as<decltype(fInnerRadius)>();
    fOuterRadius = node["OuterRadius"].as<decltype(fOuterRadius)>();
    fLength = node["Length"].as<decltype(fLength)>();
    fZPosition = node["ZPosition"].as<decltype(fZPosition)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
    fCount = node["Count"].as<decltype(fCount)>();
}

void Collimator::WriteImpl(YAML::Node& node) const {
    node["InnerRadius"] = fInnerRadius;
    node["OuterRadius"] = fOuterRadius;
    node["Length"] = fLength;
    node["ZPosition"] = fZPosition;
    node["Thickness"] = fThickness;
    node["Count"] = fCount;
}

} // namespace MACE::Core::Geometry::Description
