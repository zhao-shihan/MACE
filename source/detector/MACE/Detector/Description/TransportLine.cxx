#include "MACE/Detector/Description/SpectrometerField.hxx"
#include "MACE/Detector/Description/TransportLine.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;
using namespace PhysicalConstant;

TransportLine::TransportLine() :
    DescriptionSingletonBase<TransportLine>(__func__),
    fFirstStraightLength(20_cm),
    fFirstBendRadius(50_cm),
    fSecondStraightLength(100_cm),
    fSecondBendRadius(50_cm),
    fThirdStraightLength(20_cm),
    fSolenoidInnerRadius(7.5_cm),
    fSolenoidOuterRadius(12.5_cm),
    fFieldRadius(12.6_cm) {}

HepGeom::Transform3D TransportLine::FirstStraightTransform() const {
    const auto& spectrometerField = SpectrometerField::Instance();
    const auto transX = 0;
    const auto transY = 0;
    const auto transZ = spectrometerField.Length() / 2 + fFirstStraightLength / 2;
    return HepGeom::Transform3D(CLHEP::HepRotation(),
                                CLHEP::Hep3Vector(transX, transY, transZ));
}

HepGeom::Transform3D TransportLine::FirstBendTransform() const {
    const auto localTransX = fFirstBendRadius;
    const auto localTransY = 0;
    const auto localTransZ = fFirstStraightLength / 2;
    const auto translation = FirstStraightTransform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(CLHEP::HepXHat, halfpi), translation);
}

HepGeom::Transform3D TransportLine::SecondStraightTransform() const {
    const auto localTransX = fSecondStraightLength / 2;
    const auto localTransY = 0;
    const auto localTransZ = fFirstBendRadius;
    const auto translation = FirstBendTransform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(CLHEP::HepYHat, halfpi), translation);
}

HepGeom::Transform3D TransportLine::SecondBendTransform() const {
    const auto localTransX = fSecondStraightLength / 2;
    const auto localTransY = 0;
    const auto localTransZ = fSecondBendRadius;
    const auto translation = SecondStraightTransform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(CLHEP::HepXHat, halfpi), translation);
}

HepGeom::Transform3D TransportLine::ThirdStraightTransform() const {
    auto localTransX = fSecondBendRadius;
    auto localTransY = 0;
    auto localTransZ = fThirdStraightLength / 2;
    const auto translation = SecondBendTransform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(), translation);
}

void TransportLine::ImportValues(const YAML::Node& node) {
    ImportValue(node, fFirstStraightLength, "FirstStraightLength");
    ImportValue(node, fFirstBendRadius, "FirstBendRadius");
    ImportValue(node, fSecondStraightLength, "SecondStraightLength");
    ImportValue(node, fSecondBendRadius, "SecondBendRadius");
    ImportValue(node, fThirdStraightLength, "ThirdStraightLength");
    ImportValue(node, fSolenoidInnerRadius, "SolenoidInnerRadius");
    ImportValue(node, fSolenoidOuterRadius, "SolenoidOuterRadius");
    ImportValue(node, fFieldRadius, "FieldRadius");
}

void TransportLine::ExportValues(YAML::Node& node) const {
    ExportValue(node, fFirstStraightLength, "FirstStraightLength");
    ExportValue(node, fFirstBendRadius, "FirstBendRadius");
    ExportValue(node, fSecondStraightLength, "SecondStraightLength");
    ExportValue(node, fSecondBendRadius, "SecondBendRadius");
    ExportValue(node, fThirdStraightLength, "ThirdStraightLength");
    ExportValue(node, fSolenoidInnerRadius, "SolenoidInnerRadius");
    ExportValue(node, fSolenoidOuterRadius, "SolenoidOuterRadius");
    ExportValue(node, fFieldRadius, "FieldRadius");
}

} // namespace MACE::Geometry::Description
