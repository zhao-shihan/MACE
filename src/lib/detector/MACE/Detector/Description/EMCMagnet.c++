#include "MACE/Detector/Description/EMCMagnet.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

EMCMagnet::EMCMagnet() :
    DescriptionBase{"EMCMagnet"},
    // Geometry
    fInnerRadius{50_cm},
    fOuterRadius{55_cm},
    fLength{100_cm},
    // Material
    fMaterialName{"G4_Cu"} {}

auto EMCMagnet::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fLength, "Length");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto EMCMagnet::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fLength, "Length");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
