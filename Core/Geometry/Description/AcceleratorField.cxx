#include "Core/Geometry/Description/AcceleratorField.hxx"
#include "Utility/LiteralUnit.hxx"

#include "G4RotationMatrix.hh"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

AcceleratorField& AcceleratorField::Instance() noexcept {
    static AcceleratorField instance;
    return instance;
}

AcceleratorField::AcceleratorField() :
    IDescription("AcceleratorField"),
    fRadius(75_mm),
    fLength(100_cm),
    fDownStreamLength(90_cm) {}

G4Transform3D AcceleratorField::GetTransform() const {
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(0, 0, fDownStreamLength - fLength / 2));
}

void AcceleratorField::ReadImpl(const YAML::Node& thisNode) {
    fRadius = thisNode["Radius"].as<decltype(fRadius)>();
    fLength = thisNode["Length"].as<decltype(fLength)>();
    fDownStreamLength = thisNode["DownStreamLength"].as<decltype(fDownStreamLength)>();
}

void AcceleratorField::WriteImpl(YAML::Node& thisNode) const {
    thisNode["Radius"] = fRadius;
    thisNode["Length"] = fLength;
    thisNode["DownStreamLength"] = fDownStreamLength;
}

} // namespace MACE::Core::Geometry::Description
