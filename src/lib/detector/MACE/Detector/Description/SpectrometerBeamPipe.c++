#include "MACE/Detector/Description/SpectrometerBeamPipe.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SpectrometerBeamPipe::SpectrometerBeamPipe() :
    DescriptionSingletonBase{"SpectrometerBeamPipe"},
    fInnerRadius{80_mm},
    fThickness{500_um},
    fLength{120_cm}{}

void SpectrometerBeamPipe::ImportValues(const YAML::Node& node) {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fThickness, "Thickness");
    ImportValue(node, fLength, "Length");
}

void SpectrometerBeamPipe::ExportValues(YAML::Node& node) const {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fThickness, "Thickness");
    ExportValue(node, fLength, "Length");
}

} // namespace MACE::Detector::Description
