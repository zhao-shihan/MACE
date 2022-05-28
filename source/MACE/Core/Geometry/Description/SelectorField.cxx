#include "MACE/Core/Geometry/Description/SelectorField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

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

void SelectorField::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "Radius", fRadius);
    ReadValueNode(node, "Length", fLength);
    ReadValueNode(node, "ZPosition", fZPosition);
}

void SelectorField::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "Radius", fRadius);
    WriteValueNode(node, "Length", fLength);
    WriteValueNode(node, "ZPosition", fZPosition);
}

} // namespace MACE::Core::Geometry::Description
