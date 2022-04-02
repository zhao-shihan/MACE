#include "Core/Geometry/Description/CalorimeterField.hxx"
#include "Utility/LiteralUnit.hxx"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

CalorimeterField& CalorimeterField::Instance() noexcept {
    static CalorimeterField instance;
    return instance;
}

CalorimeterField::CalorimeterField() :
    IDescription("CalorimeterField"),
    fRadius(25_cm),
    fLength(70_cm) {}

HepGeom::Transform3D CalorimeterField::GetTransform() const {
    const auto& transportLine = TransportLine::Instance();
    const auto localTransX = 0;
    const auto localTransY = 0;
    const auto localTransZ = transportLine.GetThirdStraightLength() / 2 + fLength / 2;
    const auto translation = transportLine.ThirdStraightTransform().getTranslation() +
                             CLHEP::Hep3Vector(localTransX, localTransY, localTransZ);
    return HepGeom::Transform3D(CLHEP::HepRotation(), translation);
}

void CalorimeterField::ReadImpl(const YAML::Node& node) {
    fRadius = node["Radius"].as<decltype(fRadius)>();
    fLength = node["Length"].as<decltype(fLength)>();
}

void CalorimeterField::WriteImpl(YAML::Node& node) const {
    node["Radius"] = fRadius;
    node["Length"] = fLength;
}

} // namespace MACE::Core::Geometry::Description
