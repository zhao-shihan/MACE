#include "MACE/Detector/Description/Filter.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

Filter::Filter() :
    DescriptionSingletonBase{"Filter"},
    // Geometry
    fEnabled{true},
    fLength{100_cm},
    fRadius{49_mm},
    fThickness{200_um},
    fCount{85},
    // Material
    fMaterialName{"G4_Cu"} {}

auto Filter::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fEnabled, "Enabled");
    ImportValue(node, fLength, "Length");
    ImportValue(node, fRadius, "Radius");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fCount, "Count");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto Filter::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fEnabled, "Enabled");
    ExportValue(node, fLength, "Length");
    ExportValue(node, fRadius, "Radius");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fCount, "Count");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
