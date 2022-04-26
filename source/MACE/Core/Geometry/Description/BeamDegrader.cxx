#include "MACE/Core/Geometry/Description/BeamDegrader.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

BeamDegrader& BeamDegrader::Instance() noexcept {
    static BeamDegrader instance;
    return instance;
}

BeamDegrader::BeamDegrader() :
    IDescription("BeamDegrader"),
    fWidth(6_cm),
    fThickness(100_um),
    fDistanceToTargetSurface(5_mm) {}

HepGeom::Transform3D BeamDegrader::CalcTransform() const {
    const auto& target = Target::Instance();
    const auto transZ = target.CalcTransform().getTranslation().z() - target.GetThickness() / 2 - fThickness / 2 - fDistanceToTargetSurface;
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
}

void BeamDegrader::ReadImpl(const YAML::Node& node) {
    fWidth = node["Width"].as<decltype(fWidth)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
    fDistanceToTargetSurface = node["DistanceToTargetSurface"].as<decltype(fDistanceToTargetSurface)>();
}

void BeamDegrader::WriteImpl(YAML::Node& node) const {
    node["Width"] = fWidth;
    node["Thickness"] = fThickness;
    node["DistanceToTargetSurface"] = fDistanceToTargetSurface;
}

} // namespace MACE::Core::Geometry::Description
