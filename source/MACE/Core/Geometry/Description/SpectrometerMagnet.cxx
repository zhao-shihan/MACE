#include "MACE/Core/Geometry/Description/SpectrometerMagnet.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

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

void SpectrometerMagnet::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "InnerRadius", fInnerRadius);
    ReadValueNode(node, "OuterRadius", fOuterRadius);
    ReadValueNode(node, "Length", fLength);
}

void SpectrometerMagnet::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "InnerRadius", fInnerRadius);
    WriteValueNode(node, "OuterRadius", fOuterRadius);
    WriteValueNode(node, "Length", fLength);
}

} // namespace MACE::Core::Geometry::Description
