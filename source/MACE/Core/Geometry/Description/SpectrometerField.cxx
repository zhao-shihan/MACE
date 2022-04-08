#include "MACE/Core/Geometry/Description/SpectrometerField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

SpectrometerField& SpectrometerField::Instance() noexcept {
    static SpectrometerField instance;
    return instance;
}

SpectrometerField::SpectrometerField() :
    IDescription("SpectrometerField"),
    fRadius(71_cm),
    fLength(220_cm) {}

void SpectrometerField::ReadImpl(const YAML::Node& node) {
    fRadius = node["Radius"].as<decltype(fRadius)>();
    fLength = node["Length"].as<decltype(fLength)>();
}

void SpectrometerField::WriteImpl(YAML::Node& node) const {
    node["Radius"] = fRadius;
    node["Length"] = fLength;
}

} // namespace MACE::Core::Geometry::Description
