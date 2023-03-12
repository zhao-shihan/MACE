#include "MACE/Core/Geometry/Description/EMCalField.hxx"
#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace LiteralUnit::Length;

EMCalField::EMCalField() :
    ISingletonDescription<EMCalField>(__func__),
    fRadius(25_cm),
    fLength(70_cm) {}

HepGeom::Transform3D EMCalField::CalcTransform() const {
    const auto& transportLine = TransportLine::Instance();
    const auto localTransX = 0;
    const auto localTransY = 0;
    const auto localTransZ = transportLine.ThirdStraightLength() / 2 + fLength / 2;
    const auto translation = transportLine.ThirdStraightTransform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(), translation);
}

void EMCalField::ImportValues(const YAML::Node& node) {
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
}

void EMCalField::ExportValues(YAML::Node& node) const {
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
}

} // namespace MACE::Core::Geometry::Description
