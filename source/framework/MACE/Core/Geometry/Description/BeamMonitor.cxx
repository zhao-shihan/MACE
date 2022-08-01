#include "MACE/Core/Geometry/Description/BeamMonitor.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

BeamMonitor::BeamMonitor() :
    ISingletonDescription<BeamMonitor>(__func__),
    fIsEnabled(false),
    fWidth(4_cm),
    fThickness(500_um),
    fDistanceToTargetSurface(15_mm) {}

HepGeom::Transform3D BeamMonitor::CalcTransform() const {
    const auto& target = Target::Instance();
    const auto transZ = target.CalcTransform().getTranslation().z() - target.GetThickness() / 2 - fThickness / 2 - fDistanceToTargetSurface;
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
}

void BeamMonitor::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "IsEnabled", fIsEnabled);
    ReadValueNode(node, "Width", fWidth);
    ReadValueNode(node, "Thickness", fThickness);
    ReadValueNode(node, "DistanceToTargetSurface", fDistanceToTargetSurface);
}

void BeamMonitor::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "IsEnabled", fIsEnabled);
    WriteValueNode(node, "Width", fWidth);
    WriteValueNode(node, "Thickness", fThickness);
    WriteValueNode(node, "DistanceToTargetSurface", fDistanceToTargetSurface);
}

} // namespace MACE::Core::Geometry::Description
