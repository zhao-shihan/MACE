#include "MACE/Core/Geometry/Description/BeamDegrader.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Cxx2b/Unreachable.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

BeamDegrader::BeamDegrader() :
    ISingletonDescription<BeamDegrader>(__func__),
    fIsEnabled(true),
    fWidth(6_cm),
    fThickness(420_um),
    fDistanceToTargetSurface(5_mm) {}

HepGeom::Transform3D BeamDegrader::CalcTransform() const {
    switch (const auto& target = Target::Instance();
            target.GetShapeType()) {
    case Target::ShapeType::Cuboid:
        const auto& cuboidTarget = target.GetCuboid();
        const auto transZ = cuboidTarget.CalcTransform().getTranslation().z() - cuboidTarget.GetThickness() / 2 - fThickness / 2 - fDistanceToTargetSurface;
        return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
    }
    Cxx2b::Unreachable();
}

void BeamDegrader::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "IsEnabled", fIsEnabled);
    ReadValueNode(node, "Width", fWidth);
    ReadValueNode(node, "Thickness", fThickness);
    ReadValueNode(node, "DistanceToTargetSurface", fDistanceToTargetSurface);
}

void BeamDegrader::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "IsEnabled", fIsEnabled);
    WriteValueNode(node, "Width", fWidth);
    WriteValueNode(node, "Thickness", fThickness);
    WriteValueNode(node, "DistanceToTargetSurface", fDistanceToTargetSurface);
}

} // namespace MACE::Core::Geometry::Description
