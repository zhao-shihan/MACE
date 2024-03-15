#include "MACE/Detector/Description/EMCMagnet.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

EMCMagnet::EMCMagnet() :
    DescriptionSingletonBase{"EMCMagnet"},
    // Geometry
    fInnerRadius{50_cm},
    fOuterRadius{55_cm},
    fLength{95_cm},
    // Material
    fMaterialName{"G4_Cu"} {}

auto EMCMagnet::ImportValues(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fLength, "Length");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto EMCMagnet::ExportValues(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fLength, "Length");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
