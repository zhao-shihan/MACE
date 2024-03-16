#include "MACE/Detector/Description/SpectrometerBeamPipe.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SpectrometerBeamPipe::SpectrometerBeamPipe() :
    DescriptionSingletonBase{"SpectrometerBeamPipe"},
    fInnerRadius{10_cm},
    fBerylliumLength{100_cm},
    fBerylliumThickness{500_um},
    fAluminiumThickness{2_mm} {}

auto SpectrometerBeamPipe::ImportValues(const YAML::Node& node) -> void {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fBerylliumLength, "BerylliumLength");
    ImportValue(node, fBerylliumThickness, "BerylliumThickness");
    ImportValue(node, fAluminiumThickness, "AluminiumThickness");
}

auto SpectrometerBeamPipe::ExportValues(YAML::Node& node) const -> void {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fBerylliumLength, "BerylliumLength");
    ExportValue(node, fBerylliumThickness, "BerylliumThickness");
    ExportValue(node, fAluminiumThickness, "AluminiumThickness");
}

} // namespace MACE::Detector::Description
