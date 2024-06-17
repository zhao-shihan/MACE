#include "MACE/Detector/Description/SolenoidShield.h++"

#include "Mustard/Utility/LiteralUnit.h++"
#include "Mustard/Utility/MathConstant.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

SolenoidShield::SolenoidShield() :
    DescriptionBase{"SolenoidShield"},
    // Geometry
    fInnerRadius{100_mm},
    fOuterRadius{130_mm},
    // Material
    fMaterialName{"G4_Fe"} {}

auto SolenoidShield::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto SolenoidShield::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
