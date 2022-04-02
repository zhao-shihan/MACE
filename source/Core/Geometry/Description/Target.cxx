#include "Core/Geometry/Description/Target.hxx"
#include "Utility/LiteralUnit.hxx"

#include "G4RotationMatrix.hh"

namespace MACE::Core::Geometry::Description {

using namespace Utility::LiteralUnit::Length;

Target& Target::Instance() noexcept {
    static Target instance;
    return instance;
}

Target::Target() :
    IDescription("Target"),
    fWidth(6_cm),
    fThickness(1_cm) {}

G4Transform3D Target::GetTransform() const {
    const auto& acceleratorField = AcceleratorField::Instance();
    auto transZ = acceleratorField.GetLength() / 2 - acceleratorField.GetDownStreamLength() - fThickness / 2;
    return G4Transform3D(G4RotationMatrix(), G4ThreeVector(0, 0, transZ));
}

void Target::ReadImpl(const YAML::Node& node) {
    fWidth = node["Width"].as<decltype(fWidth)>();
    fThickness = node["Thickness"].as<decltype(fThickness)>();
}

void Target::WriteImpl(YAML::Node& node) const {
    node["Width"] = fWidth;
    node["Thickness"] = fThickness;
}

} // namespace MACE::Core::Geometry::Description
