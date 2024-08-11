#include "MACE/Detector/Description/Collimator.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

Collimator::Collimator() :
    DescriptionBase{"Collimator"},
    // Geometry
    fEnabled{true},
    fLength{500_mm},
    fRadius{49_mm},
    fThickness{0.2_mm},
    fPitch{1.15_mm},
    // Material
    fMaterialName{"G4_BRONZE"} {}

auto Collimator::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fEnabled, "Enabled");
    ImportValue(node, fLength, "Length");
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fPitch, "Pitch");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto Collimator::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fEnabled, "Enabled");
    ExportValue(node, fLength, "Length");
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fPitch, "Pitch");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
