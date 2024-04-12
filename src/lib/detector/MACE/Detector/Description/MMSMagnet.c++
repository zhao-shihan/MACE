#include "MACE/Detector/Description/MMSMagnet.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

MMSMagnet::MMSMagnet() :
    DescriptionBase{"MMSMagnet"},
    // Geometry
    fInnerRadius{55_cm},
    fOuterRadius{60_cm},
    fLength{220_cm},
    // Material
    fMaterialName{"G4_Cu"} {}

void MMSMagnet::ImportAllValue(const YAML::Node& node) {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fLength, "Length");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

void MMSMagnet::ExportAllValue(YAML::Node& node) const {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fLength, "Length");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
