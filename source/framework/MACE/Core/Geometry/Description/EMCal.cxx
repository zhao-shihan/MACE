#include "MACE/Core/Geometry/Description/EMCal.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

EMCal::EMCal() :
    ISingletonDescription<EMCal>(__func__),
    fInnerRadius(15_cm),
    fInnerLength(50_cm),
    fWindowRadius(8_cm),
    fCrystalLength(5_cm) {}

void EMCal::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "InnerRadius", fInnerRadius);
    ReadValueNode(node, "InnerLength", fInnerLength);
    ReadValueNode(node, "WindowRadius", fWindowRadius);
    ReadValueNode(node, "CrystalLength", fCrystalLength);
}

void EMCal::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "InnerRadius", fInnerRadius);
    WriteValueNode(node, "InnerLength", fInnerLength);
    WriteValueNode(node, "WindowRadius", fWindowRadius);
    WriteValueNode(node, "CrystalLength", fCrystalLength);
}

} // namespace MACE::Core::Geometry::Description
