#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

LinacField& LinacField::Instance() noexcept {
    static LinacField instance;
    return instance;
}

LinacField::LinacField() :
    IDescription("LinacField"),
    fRadius(75_mm),
    fLength(100_cm),
    fDownStreamLength(90_cm) {}

HepGeom::Transform3D LinacField::CalcTransform() const {
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, fDownStreamLength - fLength / 2));
}

void LinacField::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "Radius", fRadius);
    ReadValueNode(node, "Length", fLength);
    ReadValueNode(node, "DownStreamLength", fDownStreamLength);
}

void LinacField::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "Radius", fRadius);
    WriteValueNode(node, "Length", fLength);
    WriteValueNode(node, "DownStreamLength", fDownStreamLength);
}

} // namespace MACE::Core::Geometry::Description
