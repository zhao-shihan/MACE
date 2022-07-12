#include "MACE/Core/Geometry/Description/EMCalField.hxx"
#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

EMCalField::EMCalField() :
    IDescriptionSingleton<EMCalField>(__func__),
    fRadius(25_cm),
    fLength(70_cm) {}

HepGeom::Transform3D EMCalField::CalcTransform() const {
    const auto& transportLine = TransportLine::Instance();
    const auto localTransX = 0;
    const auto localTransY = 0;
    const auto localTransZ = transportLine.GetThirdStraightLength() / 2 + fLength / 2;
    const auto translation = transportLine.ThirdStraightTransform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(), translation);
}

void EMCalField::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "Radius", fRadius);
    ReadValueNode(node, "Length", fLength);
}

void EMCalField::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "Radius", fRadius);
    WriteValueNode(node, "Length", fLength);
}

} // namespace MACE::Core::Geometry::Description
