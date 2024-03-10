#include "MACE/Detector/Description/SpectrometerBeamPipe.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SpectrometerBeamPipe::SpectrometerBeamPipe() :
    DescriptionSingletonBase{"SpectrometerBeamPipe"},
    fInnerRadius{10_cm},
    fThickness{500_um},
    fLength{120_cm} {}

auto SpectrometerBeamPipe::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fLength, "Length");
}

auto SpectrometerBeamPipe::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fLength, "Length");
}

} // namespace MACE::Detector::Description
