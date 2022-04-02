#include "Core/Geometry/Description/SelectorField.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SelectorField& SelectorField::Instance() noexcept {
    static SelectorField instance;
    return instance;
}

SelectorField::SelectorField() :
    IDescription("SelectorField"),
    fRadius(7.5_cm),
    fLength(30_cm),
    fZPosition(20_cm) {}

void SelectorField::ReadImpl(const YAML::Node& node) {
    fRadius = node["Radius"].as<decltype(fRadius)>();
    fLength = node["Length"].as<decltype(fLength)>();
    fZPosition = node["ZPosition"].as<decltype(fZPosition)>();
}

void SelectorField::WriteImpl(YAML::Node& node) const {
    node["Radius"] = fRadius;
    node["Length"] = fLength;
    node["ZPosition"] = fZPosition;
}

} // namespace MACE::Core::Geometry::Description
