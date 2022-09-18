#include "MACE/Compatibility/std2b/unreachable.hxx"
#include "MACE/Core/Geometry/Description/BeamDegrader.hxx"
#include "MACE/Core/Geometry/Description/Target.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

BeamDegrader::BeamDegrader() :
    ISingletonDescription<BeamDegrader>(__func__),
    fIsEnabled(true),
    fWidth(6_cm),
    fThickness(430_um),
    fDistanceToTargetSurface(5_mm) {}

HepGeom::Transform3D BeamDegrader::CalcTransform() const {
    switch (const auto& target = Target::Instance();
            target.ShapeType()) {
    case Target::TargetShapeType::Cuboid:
        const auto& cuboidTarget = target.Cuboid();
        const auto transZ = cuboidTarget.CalcTransform().getTranslation().z() - cuboidTarget.Thickness() / 2 - fThickness / 2 - fDistanceToTargetSurface;
        return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
    }
    std2b::unreachable();
}

void BeamDegrader::ImportValues(const YAML::Node& node) {
    ImportValue(node, fIsEnabled, "Enabled");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fDistanceToTargetSurface, "DistanceToTargetSurface");
}

void BeamDegrader::ExportValues(YAML::Node& node) const {
    ExportValue(node, fIsEnabled, "Enabled");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fDistanceToTargetSurface, "DistanceToTargetSurface");
}

} // namespace MACE::Core::Geometry::Description
