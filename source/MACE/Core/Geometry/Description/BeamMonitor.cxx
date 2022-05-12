#include "MACE/Core/Geometry/Description/BeamMonitor.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

BeamMonitor& BeamMonitor::Instance() noexcept {
    static BeamMonitor instance;
    return instance;
}

BeamMonitor::BeamMonitor() :
    IDescription("BeamMonitor"),
    fIsEnabled(false),
    fWidth(4_cm),
    fThickness(500_um),
    fDistanceToTargetSurface(15_mm) {}

HepGeom::Transform3D BeamMonitor::CalcTransform() const {
    const auto& target = Target::Instance();
    const auto transZ = target.CalcTransform().getTranslation().z() - target.GetThickness() / 2 - fThickness / 2 - fDistanceToTargetSurface;
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
}

void BeamMonitor::ReadImpl(const YAML::Node& node) {
    fIsEnabled = node["IsEnabled"].as<decltype(fIsEnabled)>();
    fWidth = node["Width"].as<decltype(fWidth)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
    fDistanceToTargetSurface = node["DistanceToTargetSurface"].as<decltype(fDistanceToTargetSurface)>();
}

void BeamMonitor::WriteImpl(YAML::Node& node) const {
    node["IsEnabled"] = fIsEnabled;
    node["Width"] = fWidth;
    node["Thickness"] = fThickness;
    node["DistanceToTargetSurface"] = fDistanceToTargetSurface;
}

} // namespace MACE::Core::Geometry::Description
