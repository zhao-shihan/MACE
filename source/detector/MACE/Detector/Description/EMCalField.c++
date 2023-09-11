#include "MACE/Detector/Description/EMCField.h++"
#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::MagneticFluxDensity;

EMCField::EMCField() :
    DescriptionSingletonBase<EMCField>(__func__),
    // Geometry
    fRadius(25_cm),
    fLength(70_cm), 
    // Field
    fMagneticFluxDensity(100_mT) {}

HepGeom::Transform3D EMCField::CalcTransform() const {
    const auto& transportLine = Solenoid::Instance();
    const auto localTransX = 0;
    const auto localTransY = 0;
    const auto localTransZ = transportLine.S3Length() / 2 + fLength / 2;
    const auto translation = transportLine.S3Transform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(), translation);
}

void EMCField::ImportValues(const YAML::Node& node) {
    // Geometry
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fLength, "Length");
    // Field
    ImportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

void EMCField::ExportValues(YAML::Node& node) const {
    // Geometry
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fLength, "Length");
    // Field
    ExportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

} // namespace MACE::Detector::Description
