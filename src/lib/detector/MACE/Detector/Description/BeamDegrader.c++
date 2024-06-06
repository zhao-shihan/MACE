#include "MACE/Detector/Description/BeamDegrader.h++"
#include "MACE/Utility/LiteralUnit.h++"

#include "muc/utility"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

BeamDegrader::BeamDegrader() :
    DescriptionBase{"BeamDegrader"},
    fEnabled{true},
    // Geometry
    fWidth{5_cm},
    fThickness{500_um},
    fDistanceToTarget{1_cm},
    // Material
    fMaterialName{"G4_MYLAR"} {}

auto BeamDegrader::ImportAllValue(const YAML::Node& node) -> void {
    ImportValue(node, fEnabled, "Enabled");
    // Geometry
    ImportValue(node, fWidth, "Width");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fDistanceToTarget, "DistanceToTarget");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto BeamDegrader::ExportAllValue(YAML::Node& node) const -> void {
    ExportValue(node, fEnabled, "Enabled");
    // Geometry
    ExportValue(node, fWidth, "Width");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fDistanceToTarget, "DistanceToTarget");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
