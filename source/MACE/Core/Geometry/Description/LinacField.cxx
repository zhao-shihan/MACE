#include "MACE/Core/Geometry/Description/LinacField.hxx"
#include "MACE/Utility/LiteralUnit.hxx"

#include "CLHEP/Vector/Rotation.h"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

LinacField& LinacField::Instance() noexcept {
    static LinacField instance;
    return instance;
}

LinacField::LinacField() :
    IDescription("LinacField"),
    fRadius(75_mm),
    fLength(100_cm),
    fDownStreamLength(90_cm) {}

HepGeom::Transform3D LinacField::CalcTransform() const {
    return HepGeom::Transform3D(CLHEP::HepRotation(), CLHEP::Hep3Vector(0, 0, fDownStreamLength - fLength / 2));
}

void LinacField::ReadImpl(const YAML::Node& node) {
    fRadius = node["Radius"].as<decltype(fRadius)>();
    fLength = node["Length"].as<decltype(fLength)>();
    fDownStreamLength = node["DownStreamLength"].as<decltype(fDownStreamLength)>();
}

void LinacField::WriteImpl(YAML::Node& node) const {
    node["Radius"] = fRadius;
    node["Length"] = fLength;
    node["DownStreamLength"] = fDownStreamLength;
}

} // namespace MACE::Core::Geometry::Description
