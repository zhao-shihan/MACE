#include "MACE/Core/Geometry/Description/BeamCounter.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

BeamCounter& BeamCounter::Instance() noexcept {
    static BeamCounter instance;
    return instance;
}

BeamCounter::BeamCounter() :
    IDescription("BeamCounter"),
    fIsEnabled(false),
    fWidth(4_cm),
    fThickness(500_um),
    fDistanceToTargetSurface(15_mm) {}

HepGeom::Transform3D BeamCounter::CalcTransform() const {
    const auto& target = Target::Instance();
    const auto transZ = target.CalcTransform().getTranslation().z() - target.GetThickness() / 2 - fThickness / 2 - fDistanceToTargetSurface;
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
}

void BeamCounter::ReadImpl(const YAML::Node& node) {
    fIsEnabled = node["IsEnabled"].as<decltype(fIsEnabled)>();
    fWidth = node["Width"].as<decltype(fWidth)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
    fDistanceToTargetSurface = node["DistanceToTargetSurface"].as<decltype(fDistanceToTargetSurface)>();
}

void BeamCounter::WriteImpl(YAML::Node& node) const {
    node["IsEnabled"] = fIsEnabled;
    node["Width"] = fWidth;
    node["Thickness"] = fThickness;
    node["DistanceToTargetSurface"] = fDistanceToTargetSurface;
}

} // namespace MACE::Core::Geometry::Description
