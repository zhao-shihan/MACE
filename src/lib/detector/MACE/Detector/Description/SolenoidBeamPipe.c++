#include "MACE/Detector/Description/SolenoidBeamPipe.h++"
#include "MACE/Utility/LiteralUnit.h++"
#include "MACE/Utility/MathConstant.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SolenoidBeamPipe::SolenoidBeamPipe() :
    DescriptionBase{"SolenoidBeamPipe"},
    // Geometry
    fInnerRadius{50_mm},
    fThickness{2_mm},
    // Material
    fMaterialName{"G4_Al"} {}

auto SolenoidBeamPipe::ImportAllValue(const YAML::Node& node) -> void {
    // Geometry
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fThickness, "Thickness");
    // Material
    ImportValue(node, fMaterialName, "MaterialName");
}

auto SolenoidBeamPipe::ExportAllValue(YAML::Node& node) const -> void {
    // Geometry
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fThickness, "Thickness");
    // Material
    ExportValue(node, fMaterialName, "MaterialName");
}

} // namespace MACE::Detector::Description
