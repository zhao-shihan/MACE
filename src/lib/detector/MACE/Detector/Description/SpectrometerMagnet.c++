#include "MACE/Detector/Description/SpectrometerMagnet.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SpectrometerMagnet::SpectrometerMagnet() :
    DescriptionSingletonBase{"SpectrometerMagnet"},
    // Geometry
    fInnerRadius{50_cm},
    fOuterRadius{55_cm},
    fLength{218_cm},
    // Material
    fMaterialName{"G4_Cu"} {}

void SpectrometerMagnet::ImportValues(const YAML::Node& node) {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fLength, "Length");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

void SpectrometerMagnet::ExportValues(YAML::Node& node) const {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fLength, "Length");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
