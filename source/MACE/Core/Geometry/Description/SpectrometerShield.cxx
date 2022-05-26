#include "MACE/Core/Geometry/Description/SpectrometerShield.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

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

void SpectrometerShield::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "InnerRadius", fInnerRadius);
    ReadValueNode(node, "InnerLength", fInnerLength);
    ReadValueNode(node, "WindowRadius", fWindowRadius);
    ReadValueNode(node, "Thickness", fThickness);
}

void SpectrometerShield::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "InnerRadius", fInnerRadius);
    WriteValueNode(node, "InnerLength", fInnerLength);
    WriteValueNode(node, "WindowRadius", fWindowRadius);
    WriteValueNode(node, "Thickness", fThickness);
}

} // namespace MACE::Core::Geometry::Description
