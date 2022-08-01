#include "MACE/Core/Geometry/Description/EMCalShield.hxx"
#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

EMCalShield::EMCalShield() :
    ISingletonDescription<EMCalShield>(__func__),
    fInnerRadius(30_cm),
    fInnerLength(80_cm),
    fWindowRadius(12.7_cm),
    fThickness(5_cm) {}

void EMCalShield::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "InnerRadius", fInnerRadius);
    ReadValueNode(node, "InnerLength", fInnerLength);
    ReadValueNode(node, "WindowRadius", fWindowRadius);
    ReadValueNode(node, "Thickness", fThickness);
}

void EMCalShield::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "InnerRadius", fInnerRadius);
    WriteValueNode(node, "InnerLength", fInnerLength);
    WriteValueNode(node, "WindowRadius", fWindowRadius);
    WriteValueNode(node, "Thickness", fThickness);
}

} // namespace MACE::Core::Geometry::Description
