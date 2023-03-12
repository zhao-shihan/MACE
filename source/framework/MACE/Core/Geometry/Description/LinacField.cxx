#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace LiteralUnit::Length;

LinacField::LinacField() :
    ISingletonDescription<LinacField>(__func__),
    fRadius(75_mm),
    fLength(100_cm),
    fDownStreamLength(90_cm) {}

HepGeom::Transform3D LinacField::CalcTransform() const {
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, fDownStreamLength - fLength / 2));
}

void LinacField::ImportValues(const YAML::Node& node) {
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    ImportValue(node, fDownStreamLength, "DownStreamLength");
}

void LinacField::ExportValues(YAML::Node& node) const {
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    ExportValue(node, fDownStreamLength, "DownStreamLength");
}

} // namespace MACE::Core::Geometry::Description
