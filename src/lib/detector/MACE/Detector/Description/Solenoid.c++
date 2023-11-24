#include "MACE/Detector/Description/Solenoid.h++"
#include "MACE/Detector/Description/SpectrometerField.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace LiteralUnit::MagneticFluxDensity;
using namespace MathConstant;

Solenoid::Solenoid() :
    DescriptionSingletonBase<Solenoid>(__func__),
    // Geometry
    fS1Length(20_cm),
    fB1Radius(50_cm),
    fS2Length(100_cm),
    fB2Radius(50_cm),
    fS3Length(20_cm),
    fInnerRadius(2.5_cm),
    fOuterRadius(7.5_cm),
    fFieldRadius(7.6_cm),
    // Field
    fMagneticFluxDensity(100_mT) {}

HepGeom::Transform3D Solenoid::S1Transform() const {
    const auto& spectrometerField = SpectrometerField::Instance();
    const auto transX = 0;
    const auto transY = 0;
    const auto transZ = spectrometerField.Length() / 2 + fS1Length / 2;
    return HepGeom::Transform3D(CLHEP::HepRotation(),
                                CLHEP::Hep3Vector(transX, transY, transZ));
}

HepGeom::Transform3D Solenoid::B1Transform() const {
    const auto localTransX = fB1Radius;
    const auto localTransY = 0;
    const auto localTransZ = fS1Length / 2;
    const auto translation = S1Transform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(CLHEP::HepXHat, pi / 2), translation);
}

HepGeom::Transform3D Solenoid::S2Transform() const {
    const auto localTransX = fS2Length / 2;
    const auto localTransY = 0;
    const auto localTransZ = fB1Radius;
    const auto translation = B1Transform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(CLHEP::HepYHat, pi / 2), translation);
}

HepGeom::Transform3D Solenoid::B2Transform() const {
    const auto localTransX = fS2Length / 2;
    const auto localTransY = 0;
    const auto localTransZ = fB2Radius;
    const auto translation = S2Transform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(CLHEP::HepXHat, pi / 2), translation);
}

HepGeom::Transform3D Solenoid::S3Transform() const {
    auto localTransX = fB2Radius;
    auto localTransY = 0;
    auto localTransZ = fS3Length / 2;
    const auto translation = B2Transform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(), translation);
}

void Solenoid::ImportValues(const YAML::Node& node) {
    // Geometry
    ImportValue(node, fS1Length, "S1Length");
    ImportValue(node, fB1Radius, "B1Radius");
    ImportValue(node, fS2Length, "S2Length");
    ImportValue(node, fB2Radius, "B2Radius");
    ImportValue(node, fS3Length, "S3Length");
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fFieldRadius, "FieldRadius");
    // Field
    ImportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

void Solenoid::ExportValues(YAML::Node& node) const {
    // Geometry
    ExportValue(node, fS1Length, "S1Length");
    ExportValue(node, fB1Radius, "B1Radius");
    ExportValue(node, fS2Length, "S2Length");
    ExportValue(node, fB2Radius, "B2Radius");
    ExportValue(node, fS3Length, "S3Length");
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fFieldRadius, "FieldRadius");
    // Field
    ExportValue(node, fMagneticFluxDensity, "MagneticFluxDensity");
}

} // namespace MACE::Detector::Description
