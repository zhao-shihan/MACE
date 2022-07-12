#include "MACE/Core/Geometry/Description/Collimator.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Collimator::Collimator() :
    IDescriptionSingleton<Collimator>(__func__),
    fInnerRadius(5_mm),
    fOuterRadius(65_mm),
    fLength(30_cm),
    fZPosition(-20_cm),
    fThickness(0.75_mm),
    fCount(7) {}

void Collimator::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "InnerRadius", fInnerRadius);
    ReadValueNode(node, "OuterRadius", fOuterRadius);
    ReadValueNode(node, "Length", fLength);
    ReadValueNode(node, "ZPosition", fZPosition);
    ReadValueNode(node, "Thickness", fThickness);
    ReadValueNode(node, "Count", fCount);
}

void Collimator::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "InnerRadius", fInnerRadius);
    WriteValueNode(node, "OuterRadius", fOuterRadius);
    WriteValueNode(node, "Length", fLength);
    WriteValueNode(node, "ZPosition", fZPosition);
    WriteValueNode(node, "Thickness", fThickness);
    WriteValueNode(node, "Count", fCount);
}

} // namespace MACE::Core::Geometry::Description
