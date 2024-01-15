#include "MACE/Detector/Description/SpectrometerMagnet.h++"
#include "MACE/Utility/LiteralUnit.h++"

namespace MACE::Detector::Description {

using namespace LiteralUnit::Length;

SpectrometerMagnet::SpectrometerMagnet() :
    DescriptionSingletonBase<SpectrometerMagnet>{"SpectrometerMagnet"},
    fInnerRadius{50_cm},
    fOuterRadius{60_cm},
    fLength{218_cm} {}

void SpectrometerMagnet::ImportValues(const YAML::Node& node) {
    ImportValue(node, fInnerRadius, "InnerRadius");
    ImportValue(node, fOuterRadius, "OuterRadius");
    ImportValue(node, fLength, "Length");
}

void SpectrometerMagnet::ExportValues(YAML::Node& node) const {
    ExportValue(node, fInnerRadius, "InnerRadius");
    ExportValue(node, fOuterRadius, "OuterRadius");
    ExportValue(node, fLength, "Length");
}

} // namespace MACE::Detector::Description
