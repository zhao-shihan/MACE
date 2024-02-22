#include "MACE/Compatibility/std23/unreachable.h++"
#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Detector/Description/Target.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

BeamDegrader::BeamDegrader() :
    DescriptionSingletonBase{"BeamDegrader"},
    fEnabled{true},
    fWidth{6_cm},
    fThickness{430_um},
    fDistanceToTargetSurface{5_mm} {}

HepGeom::Transform3D BeamDegrader::CalcTransform() const {
    switch (const auto& target = Target::Instance();
            target.ShapeType()) {
    case Target::TargetShapeType::Cuboid:
        const auto& cuboidTarget = target.Cuboid();
        const auto transZ = cuboidTarget.CalcTransform().getTranslation().z() - cuboidTarget.Thickness() / 2 - fThickness / 2 - fDistanceToTargetSurface;
        return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, transZ));
    }
    std23::unreachable();
}

auto BeamDegrader::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fEnabled, "Enabled");
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fDistanceToTargetSurface, "DistanceToTargetSurface");
}

auto BeamDegrader::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fEnabled, "Enabled");
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fDistanceToTargetSurface, "DistanceToTargetSurface");
}

} // namespace MACE::Detector::Description
