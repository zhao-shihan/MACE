#include "MACE/Core/Geometry/Description/SpectrometerField.hxx"
#include "MACE/Core/Geometry/Description/TransportLine.hxx"
#include "MACE/Utility/LiteralUnit.hxx"
#include "MACE/Utility/PhysicalConstant.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;
using namespace Utility::PhysicalConstant;

TransportLine::TransportLine() :
    IDescriptionSingleton<TransportLine>("TransportLine"),
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
    const auto transZ = spectrometerField.GetLength() / 2 + fFirstStraightLength / 2;
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

void TransportLine::ReadDescriptionNode(const YAML::Node& node) {
    ReadValueNode(node, "FirstStraightLength", fFirstStraightLength);
    ReadValueNode(node, "FirstBendRadius", fFirstBendRadius);
    ReadValueNode(node, "SecondStraightLength", fSecondStraightLength);
    ReadValueNode(node, "SecondBendRadius", fSecondBendRadius);
    ReadValueNode(node, "ThirdStraightLength", fThirdStraightLength);
    ReadValueNode(node, "SolenoidInnerRadius", fSolenoidInnerRadius);
    ReadValueNode(node, "SolenoidOuterRadius", fSolenoidOuterRadius);
    ReadValueNode(node, "FieldRadius", fFieldRadius);
}

void TransportLine::WriteDescriptionNode(YAML::Node& node) const {
    WriteValueNode(node, "FirstStraightLength", fFirstStraightLength);
    WriteValueNode(node, "FirstBendRadius", fFirstBendRadius);
    WriteValueNode(node, "SecondStraightLength", fSecondStraightLength);
    WriteValueNode(node, "SecondBendRadius", fSecondBendRadius);
    WriteValueNode(node, "ThirdStraightLength", fThirdStraightLength);
    WriteValueNode(node, "SolenoidInnerRadius", fSolenoidInnerRadius);
    WriteValueNode(node, "SolenoidOuterRadius", fSolenoidOuterRadius);
    WriteValueNode(node, "FieldRadius", fFieldRadius);
}

} // namespace MACE::Core::Geometry::Description
