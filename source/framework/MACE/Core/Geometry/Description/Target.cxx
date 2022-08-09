#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Target::Target() :
    ISingletonDescription<Target>(__func__),
    fShape(ShapeType::Cuboid),
    fCuboid() {}

void Target::ReadDescriptionNode(const YAML::Node& /* node */) {
    /* ReadValueNode(node, "Width", fWidth);
    ReadValueNode(node, "Thickness", fThickness);
    ReadValueNode<double>(node, "AblationExtent", [this](auto value) { fHole->SetExtent(value); });
    ReadValueNode<double>(node, "HoleSpacing", [this](auto value) { fHole->SetSpacing(value); });
    ReadValueNode<double>(node, "HoleDiameter", [this](auto value) { fHole->SetDiameter(value); });
    ReadValueNode<double>(node, "HoleDepth", [this](auto value) { fHole->SetDepth(value); }); */
}

void Target::WriteDescriptionNode(YAML::Node& /* node */) const {
    /* WriteValueNode(node, "Width", fWidth);
    WriteValueNode(node, "Thickness", fThickness);
    WriteValueNode(node, "AblationExtent", fHole->GetExtent());
    WriteValueNode(node, "HoleSpacing", fHole->GetSpacing());
    WriteValueNode(node, "HoleDiameter", fHole->GetDiameter());
    WriteValueNode(node, "HoleDepth", fHole->GetDepth()); */
}

Target::Cuboid::Cuboid() :
    fWidth(6_cm),
    fThickness(1_cm),
    fDetail(DetailType::Hole),
    fHole() {}

HepGeom::Transform3D Target::Cuboid::CalcTransform() const {
    const auto& linacField = LinacField::Instance();
    const auto transZ = linacField.GetLength() / 2 - linacField.GetDownStreamLength() - fThickness / 2;
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
}

Target::Cuboid::Hole::Hole() :
    DetailBase<Hole>(),
    fHalfExtent(4_cm / 2),
    fSpacing(175_um),
    fRadius(49.5_um / 2),
    fDepth(3_mm),
    fPitch(fSpacing + 2 * fRadius) {}

void Target::Cuboid::Hole::SetSpacing(double spacing) {
    fSpacing = spacing;
    fPitch = spacing + 2 * fRadius;
}

void Target::Cuboid::Hole::SetDiameter(double diameter) {
    fRadius = diameter / 2;
    fPitch = fSpacing + diameter;
}

} // namespace MACE::Core::Geometry::Description
