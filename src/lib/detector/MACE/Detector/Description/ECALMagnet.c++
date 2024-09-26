#include "MACE/Detector/Description/ECALMagnet.h++"

#include "Mustard/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace Mustard::LiteralUnit::Length;

ECALMagnet::ECALMagnet() :
    DescriptionBase{"ECALMagnet"},
    // Geometry
    fInnerRadius{50_cm},
    fOuterRadius{55_cm},
    fLength{100_cm},
    // Material
    fMaterialName{"G4_Cu"} {}

auto ECALMagnet::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fLength, "Length");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto ECALMagnet::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fLength, "Length");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
